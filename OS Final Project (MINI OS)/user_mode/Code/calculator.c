#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

static GtkWidget *entry;

double evaluate_expression(const char *expression);

void on_button_clicked(GtkWidget *widget, gpointer data)
{
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON(widget));
    const gchar *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    gchar *new_text;

    if (g_strcmp0(button_label, "=") == 0)
    {
        double result = evaluate_expression(current_text);
        new_text = g_strdup_printf("%f", result);
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
        g_free(new_text);
    }
    else if (g_strcmp0(button_label, "C") == 0)
    {
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    }
    else
    {
        new_text = g_strdup_printf("%s%s", current_text, button_label);
        gtk_entry_set_text(GTK_ENTRY(entry), new_text);
        g_free(new_text);
    }
}

double evaluate_expression(const char *expression)
{
    // Note: This is a very simple expression evaluator for demo purposes
    // It supports +, -, *, / operations and does not handle errors robustly
    char operator= 0;
    double num1 = 0, num2 = 0;
    sscanf(expression, "%lf %c %lf", &num1, &operator, & num2);

    switch (operator)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num2 != 0 ? num1 / num2 : 0;
    default:
        return 0;
    }
}

void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *heading_label;
    GtkCssProvider *css_provider;
    gchar *buttons[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"};

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 250);

    heading_label = gtk_label_new("Calculator");
    gtk_widget_set_name(heading_label, "heading_label");

    entry = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE);

    grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), heading_label, 0, 0, 4, 1);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 1, 4, 1);

    for (int i = 0; i < 16; i++)
    {
        button = gtk_button_new_with_label(buttons[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, (i / 4) + 2, 1, 1);
    }

    button = gtk_button_new_with_label("C");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 6, 4, 1);

    gtk_container_add(GTK_CONTAINER(window), grid);

    css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider,
                                    "#heading_label {"
                                    "  color: white;"
                                    "  background-color: #4CAF50;"
                                    "  font-size: 24px;"
                                    "  padding: 10px;"
                                    "  text-align: center;"
                                    "}"
                                    "entry {"
                                    "  font-size: 18px;"
                                    "}"
                                    "button {"
                                    "  font-size: 18px;"
                                    "  padding: 10px;"
                                    "}",
                                    -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(css_provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.Calculator", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
