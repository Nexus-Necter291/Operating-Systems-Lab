#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

#define CELL_SIZE 20
#define GRID_WIDTH 30
#define GRID_HEIGHT 20
#define BORDER_WIDTH 4 // Adjust the border width as needed

typedef struct
{
    int x, y;
} Point;

typedef struct
{
    Point body[GRID_WIDTH * GRID_HEIGHT];
    int length;
    Point direction;
} Snake;

typedef struct
{
    Point position;
} Food;

Snake snake;
Food food;
int score = 0;
gboolean game_over = FALSE;

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_Up && snake.direction.y != 1)
    {
        snake.direction.x = 0;
        snake.direction.y = -1;
    }
    else if (event->keyval == GDK_KEY_Down && snake.direction.y != -1)
    {
        snake.direction.x = 0;
        snake.direction.y = 1;
    }
    else if (event->keyval == GDK_KEY_Left && snake.direction.x != 1)
    {
        snake.direction.x = -1;
        snake.direction.y = 0;
    }
    else if (event->keyval == GDK_KEY_Right && snake.direction.x != -1)
    {
        snake.direction.x = 1;
        snake.direction.y = 0;
    }
    return TRUE;
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    if (game_over)
    {
        cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 40);
        cairo_move_to(cr, 50, 150);
        cairo_show_text(cr, "Game Over");
        cairo_set_font_size(cr, 20);
        cairo_move_to(cr, 50, 200);
        cairo_show_text(cr, "Press R to Restart");
        return FALSE;
    }

    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_paint(cr);

    // Draw border
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_set_line_width(cr, BORDER_WIDTH);
    cairo_rectangle(cr, BORDER_WIDTH / 2, BORDER_WIDTH / 2, GRID_WIDTH * CELL_SIZE - BORDER_WIDTH, GRID_HEIGHT * CELL_SIZE - BORDER_WIDTH);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    for (int i = 0; i < snake.length; i++)
    {
        cairo_rectangle(cr, snake.body[i].x * CELL_SIZE, snake.body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    }
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    cairo_rectangle(cr, food.position.x * CELL_SIZE, food.position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 20);
    cairo_move_to(cr, 10, 30);
    char score_text[50];
    sprintf(score_text, "Score: %d", score);
    cairo_show_text(cr, score_text);

    return FALSE;
}

static void move_snake()
{
    if (game_over)
        return;

    Point new_head = {
        .x = snake.body[0].x + snake.direction.x,
        .y = snake.body[0].y + snake.direction.y};

    if (new_head.x < 0 || new_head.x >= GRID_WIDTH || new_head.y < 0 || new_head.y >= GRID_HEIGHT)
    {
        game_over = TRUE;
        return;
    }

    for (int i = 0; i < snake.length; i++)
    {
        if (new_head.x == snake.body[i].x && new_head.y == snake.body[i].y)
        {
            game_over = TRUE;
            return;
        }
    }

    for (int i = snake.length - 1; i > 0; i--)
    {
        snake.body[i] = snake.body[i - 1];
    }
    snake.body[0] = new_head;

    if (new_head.x == food.position.x && new_head.y == food.position.y)
    {
        snake.length++;
        score++;
        food.position.x = rand() % GRID_WIDTH;
        food.position.y = rand() % GRID_HEIGHT;
    }
}

static gboolean on_timeout(gpointer data)
{
    move_snake();
    gtk_widget_queue_draw(GTK_WIDGET(data));
    return TRUE;
}

static void restart_game()
{
    game_over = FALSE;
    score = 0;
    snake.length = 1;
    snake.body[0].x = GRID_WIDTH / 2;
    snake.body[0].y = GRID_HEIGHT / 2;
    snake.direction.x = 1;
    snake.direction.y = 0;
    food.position.x = rand() % GRID_WIDTH;
    food.position.y = rand() % GRID_HEIGHT;
}

static gboolean on_key_press_event(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_r || event->keyval == GDK_KEY_R)
    {
        restart_game();
    }
    else
    {
        on_key_press(widget, event, data);
    }
    return TRUE;
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    srand(time(NULL));

    restart_game();

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press_event), NULL);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), NULL);
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_timeout_add(100, on_timeout, drawing_area);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
