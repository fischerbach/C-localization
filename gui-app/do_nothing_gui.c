#include <gtk/gtk.h>

typedef struct {
    int green;
    GtkWidget *window;
} dialog_arguments;

void end_program(GtkWidget *widget, gpointer ptr);
static void file_selected(GtkFileChooserButton *btn, gpointer ptr);
void open_dialog(GtkWidget *widget, gpointer ptr);
void update_green_option(GtkWidget *widget, gpointer ptr);

int main(int argc, char *argv[]) {
    gtk_init (&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *main_table = gtk_table_new(2, 2, TRUE);

    GtkWidget *select_file_button = gtk_file_chooser_button_new("Select file", GTK_FILE_CHOOSER_ACTION_OPEN);
    GtkWidget *do_nothing_button = gtk_button_new_with_label ("Do nothing.");
    gtk_widget_set_sensitive (do_nothing_button, FALSE);
    GtkWidget *green_checkbox = gtk_check_button_new_with_label("green");
    
    gtk_window_set_title(GTK_WINDOW(window), "Do Nothing");
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 75);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_focus(GTK_WINDOW(window), NULL);

    g_signal_connect(window, "delete_event", G_CALLBACK(end_program), NULL);
    g_signal_connect (select_file_button, "file-set", G_CALLBACK (file_selected), do_nothing_button);

    dialog_arguments da = {0, window};
    g_signal_connect(green_checkbox, "toggled", G_CALLBACK(update_green_option), &da);
    g_signal_connect(do_nothing_button, "clicked", G_CALLBACK(open_dialog), &da);

    gtk_table_attach_defaults(GTK_TABLE(main_table), select_file_button, 0, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(main_table), do_nothing_button, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(main_table), green_checkbox, 1, 2, 1, 2);

    gtk_container_add(GTK_CONTAINER(window), main_table);
    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}


void end_program(GtkWidget *widget, gpointer ptr) {
    gtk_main_quit();
}

static void file_selected(GtkFileChooserButton *btn, gpointer ptr) {
    gtk_widget_set_sensitive (GTK_WIDGET(ptr), TRUE);
}

void open_dialog(GtkWidget *widget, gpointer ptr) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("", GTK_WINDOW(((dialog_arguments *)ptr)->window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "Cancel", 0, "OK", 1, NULL);

    GtkWidget *label = gtk_label_new ("Doing nothing.");
    gtk_container_add (GTK_CONTAINER (gtk_dialog_get_content_area (GTK_DIALOG (dialog))), label);

    printf("%d",1);

    if (((dialog_arguments *)ptr)->green) {
        gtk_label_set_markup (GTK_LABEL (label), "<span foreground='#27ae60'>Doing nothing in green.</span>");
    }
    gtk_widget_show (label);

    int result = gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void update_green_option(GtkWidget *widget, gpointer ptr) {
    ((dialog_arguments *)ptr)->green = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
}
