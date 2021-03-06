#include "assets.h"

/*------Fonction affichant le menu------*/

ChoixMenu menu(){
  int clic;
  int x,y;
  ChoixMenu choix;
  MLV_Music *menu1, *menu2, *menu_intro;
  MLV_Font *font1, *font2;
  MLV_Image *image;

  MLV_create_window("menu", "menu", 400, 800);
  MLV_init_audio();

  image = MLV_load_image("ressources/assets/issou_corp.png");
  menu1 = MLV_load_music("ressources/OST/menu1.wav");
  menu2 = MLV_load_music("ressources/OST/menu2.wav");
  menu_intro = MLV_load_music("ressources/OST/menu_intro.wav");
  font1 = MLV_load_font("ressources/polices/TravelingTypewriter.ttf", 40);
  font2 = MLV_load_font("ressources/polices/police_anc.ttf", 200);

  MLV_draw_filled_rectangle(0, 0, 400, 800, MLV_COLOR_GREY15);
  MLV_draw_text_with_font(50, 250, "Created by :", font1, MLV_COLOR_RED2);
  MLV_draw_text_with_font(70, 300, "Soam LE DORTZ", font1, MLV_COLOR_RED2);
  MLV_draw_text_with_font(70, 350, "Enzo CADONI", font1, MLV_COLOR_RED2);
  MLV_actualise_window();
  MLV_play_music(menu1, 0.6, 1);
  MLV_wait_mouse_or_seconds(NULL, NULL, 4);
  MLV_free_music(menu1);

  MLV_draw_filled_rectangle(0, 0, 400, 800, MLV_COLOR_GREY15);
  MLV_resize_image_with_proportions( image, 400, 400);
  MLV_draw_image(image, 0, 100);
  MLV_draw_text_with_font(90, 500, "Issou Corp", font1, MLV_COLOR_RED2);
  MLV_actualise_window();
  MLV_play_music(menu2, 0.6, 1);
  MLV_wait_mouse_or_seconds(NULL, NULL, 4);
  MLV_free_music(menu2);
  MLV_free_font(font1);

  MLV_play_music(menu_intro, 0.6, -1);
  clic = 0;
  while(clic == 0){
    MLV_draw_filled_rectangle(0, 0, 800, 800, MLV_COLOR_BLACK);
    font2 = MLV_load_font("ressources/polices/police_anc.ttf", 100);
    MLV_draw_text_with_font(30, 60, "V", font2, MLV_COLOR_RED2);
    MLV_draw_text_with_font(220, 60, "G", font2, MLV_COLOR_RED2);
    MLV_free_font(font2);

    font2 = MLV_load_font("ressources/polices/police_anc.ttf", 70);
    MLV_draw_text_with_font(70, 220, "CHESS", font2, MLV_COLOR_RED2);
    MLV_free_font(font2);

    font2 = MLV_load_font("ressources/polices/police_anc.ttf", 40);
    MLV_draw_text_with_font(110, 120, "ery", font2, MLV_COLOR_RED2);
    MLV_draw_text_with_font(290, 120, "ood", font2, MLV_COLOR_RED2);

    MLV_draw_text_with_font(150, 390, "Play", font2, MLV_COLOR_RED2);
    MLV_draw_text_with_font(140, 470, "Editor", font2, MLV_COLOR_RED2);
    MLV_draw_text_with_font(150, 550, "Load", font2, MLV_COLOR_RED2);
    MLV_draw_text_with_font(130, 630, "Quitter", font2, MLV_COLOR_RED2);
    MLV_draw_text_with_font(90, 710, "Leaderboard", font2, MLV_COLOR_RED2);
    MLV_get_mouse_position(&x, &y);

    if(x > 150 && x < 250 && y > 390 && y < 440){
      MLV_free_font(font2);
      font2 = MLV_load_font("ressources/polices/police_anc.ttf", 45);
      MLV_draw_text_with_font(145, 385, "Play", font2, MLV_COLOR_ORANGE);
      if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED ){
        clic = 1;
        choix = Play;
      }
    }

    if(x > 130 && x < 270 && y > 470 && y < 520){
      MLV_free_font(font2);
      font2 = MLV_load_font("ressources/polices/police_anc.ttf", 44);
      MLV_draw_text_with_font(135, 465, "Editor", font2, MLV_COLOR_ORANGE);
      if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED ){
        clic = 1;
        choix = Editor;
      }
    }

    if(x > 150 && x < 250 && y > 550 && y < 600){
      MLV_free_font(font2);
      font2 = MLV_load_font("ressources/polices/police_anc.ttf", 45);
      MLV_draw_text_with_font(143, 545, "Load", font2, MLV_COLOR_ORANGE);
      if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED ){
        clic = 1;
        choix = Load;
      }
    }

    if(x > 130 && x < 270 && y > 630 && y < 680){
      MLV_free_font(font2);
      font2 = MLV_load_font("ressources/polices/police_anc.ttf", 44);
      MLV_draw_text_with_font(125, 625, "Quitter", font2, MLV_COLOR_ORANGE);
      if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED ){
        clic = 1;
        choix = Quit;
      }
    }

    if(x > 90 && x < 300 && y > 710 && y < 750){
      MLV_free_font(font2);
      font2 = MLV_load_font("ressources/polices/police_anc.ttf", 43);
      MLV_draw_text_with_font(85, 705, "Leaderboard", font2, MLV_COLOR_ORANGE);
      if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED ){
        clic = 1;
        choix = Leaderboard;
      }
    }
    if(clic != 1){
      MLV_actualise_window();
      MLV_free_font(font2);
    }
  }
  MLV_free_audio();
  MLV_free_music(menu_intro);
  MLV_free_window();
  return choix;
}
