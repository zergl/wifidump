#include <gtk/gtk.h>

#define APPNAME "WIFI Dump "
#define AUTHOR_NAME "Yi Ling"
#define AUTHOR_EMAIL "e3.gemini@qq.com"

GtkWidget *menu;

void show_about_info()
{
	GtkWidget *w, *label, *tv;
	//w = gtk_window_new(GTK_WINDOW_POPUP);
	w = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//g_signal_connect(G_OBJECT(w), "clicked", gtk_main_quit, NULL);
	//g_signal_connect(G_OBJECT(w), "destroy", gtk_main_quit, NULL);
	

	gtk_window_set_title(GTK_WINDOW(w), "ABOUT - "APPNAME);
	gtk_window_set_position(GTK_WINDOW(w), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(w), 300, 180);
	

	/*
	tv = gtk_text_view_new();
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
	//gtk_text_view_set_text(GTK_TEXT_VIEW(tv), "hello");
	
	gtk_container_add(GTK_CONTAINER(w), tv);
	*/
	//gchar *text= "WIFI Dump -- A tool to dump wifi info.";
	time_t now;
	struct tm *t2;
	time(&now);
	t2 = localtime(&now);
	gchar text[256] = {0};
	snprintf(text,
		255, 
		"[ %s]\nA tool for dumping wifi connection infomation.\n\n"
		"Author:\t%s\n"
		" Email:\t%s\n"
		"  Date:\t%s\n\n\n",
		APPNAME, 
		AUTHOR_NAME, 
		AUTHOR_EMAIL,
		//asctime(gmtime(&now)
		asctime(t2));

	label = gtk_label_new(text);
	gtk_container_add(GTK_CONTAINER(w), label);

	gtk_widget_show_all(w);
}

void show_wifi_stat()
{
	GtkWidget *w, *label, *tv;
	//w = gtk_window_new(GTK_WINDOW_POPUP);
	w = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//g_signal_connect(G_OBJECT(w), "clicked", gtk_main_quit, NULL);
	//g_signal_connect(G_OBJECT(w), "destroy", gtk_main_quit, NULL);
	

	gtk_window_set_title(GTK_WINDOW(w), "Stat Info under monitoring");
	gtk_window_set_position(GTK_WINDOW(w), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(w), 300, 180);
	

	//label = gtk_label_new(text);
	//gtk_container_add(GTK_CONTAINER(w), label);

	gtk_widget_show_all(w);
}


void init_menu()
{
	menu = gtk_menu_new();
	GtkWidget *item;
	
	item = gtk_menu_item_new_with_label(APPNAME);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	
	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	
	item = gtk_menu_item_new_with_label("Scanning");
	g_signal_connect(G_OBJECT(item), "activate", NULL, NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	
	item = gtk_menu_item_new_with_label("Settings...");
	g_signal_connect(G_OBJECT(item), "activate", NULL, NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	
	item = gtk_menu_item_new_with_label("Restart WLAN");
	g_signal_connect(G_OBJECT(item), "activate", NULL, NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	
	item = gtk_menu_item_new_with_label("Monitoring");
	g_signal_connect(G_OBJECT(item), "activate", show_wifi_stat, NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	
	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	
	item = gtk_menu_item_new_with_label("About");
	g_signal_connect(G_OBJECT(item), "activate", show_about_info, NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	
	item = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

	item = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
	g_signal_connect(G_OBJECT(item), "activate", gtk_main_quit, NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
}

void show_menu(GtkStatusIcon *icon, guint button, guint activate_time, gpointer pos)
{
	gtk_menu_popup(GTK_MENU(menu),
		NULL, NULL, NULL,NULL,
		button,
		activate_time);
	gtk_widget_show_all(GTK_WIDGET(menu));
}

int main(int argc, char **argv)
{
	gtk_init(&argc, &argv);

	GtkStatusIcon *icon = gtk_status_icon_new_from_file("./icon/w2.png");
	if(icon == NULL)
	{
		fprintf(stderr, "failed to load icon file.\n");
		return -1;
	}

	gtk_status_icon_set_tooltip(icon, APPNAME);
	gtk_status_icon_set_visible(icon, (gboolean)TRUE);

	init_menu();
	g_signal_connect(G_OBJECT(icon), "popup_menu", G_CALLBACK(show_menu), icon);
	
	daemon();
	gtk_main();

	return 0;
}

