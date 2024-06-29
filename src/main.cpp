#include "bn_core.h"
#include "bn_log.h"
#include "bn_string.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_font.h"
#include "bn_random.h"
#include "bn_unordered_map.h"


#include "bn_sprite_items_keyboard_ptr.h"
#include "bn_sprite_items_keyboard_bg.h"
#include "bn_regular_bg_items_green.h"
#include "bn_regular_bg_items_keyboard.h"
#include "bn_sprite_items_backspace.h"
#include "bn_sprite_items_enter.h"
#include "bn_sprite_items_space.h"
#include "bn_sprite_items_fixed_8x16_font.h"
#include "fixed_32x64_sprite_font.h"



#include "common_fixed_8x16_sprite_font.h"

namespace {
    enum Keypad_Type {
        RIGHT, LEFT, UP, DOWN, A_BUTTON, NONE
    };

    enum Response_State {
        USER_RESPONDING, COMPUTER_RESPONDING, USER_WAITING
    };

    char get_pointed_char(int keyboard_pointer_x, int keyboard_pointer_y) {
        bn::string<31> alphabet = "qwertyuiopasdfghjkl?zxcvbnm   ";
        return alphabet[keyboard_pointer_y * 10 + keyboard_pointer_x];
    }


    void generate_wrapped_text(bn::sprite_text_generator* generator, bn::string<200> text, int start_x, int start_y, int max_x, bn::vector<bn::sprite_ptr, 52> text_sprites) {
        
        generator->generate(start_x, start_y, text, text_sprites);
        
        int x = start_x;
        int y = start_y;
        for (char c : text) {
            if (x >= max_x) {
                x = start_x;
                y += 10;
            }
            bn::string<1> char_text;
            bn::ostringstream text_stream(char_text);
            text_stream.append(c);
            
            generator->generate(x, y, char_text, text_sprites);
            x += 10;
        }
    }

    bn::string<12> build_response_message(bn::string<60> user_response, bn::string<60> computer_response_so_far, bn::random rand) {
        if (computer_response_so_far.length() > 40) {
            return "";
        }
        /* START GENERATED CODE */
        if (computer_response_so_far.length() == 0) {
            if (rand.get_unbiased_int(0, 2) == 0) return "1" ;
            if (rand.get_unbiased_int(0, 1) == 0) return "2" ;
        }
        if (computer_response_so_far.at(0) == '1') {
            if (computer_response_so_far.length() == 1) {
                if (rand.get_unbiased_int(0, 2) == 0) return "x" ;
                if (rand.get_unbiased_int(0, 1) == 0) return "y" ;
            }
        }
        if (computer_response_so_far.at(0) == '2') {
            if (computer_response_so_far.length() == 1) {
                if (rand.get_unbiased_int(0, 2) == 0) return "a" ;
                if (rand.get_unbiased_int(0, 1) == 0) return "b" ;
            }
        }
        /* END GENERATED CODE */
        return "";
    }
}

int main()
{
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(30, 30, 29));

    bn::sprite_text_generator keyboard_text_generator(fixed_32x64_sprite_font);
    keyboard_text_generator.set_right_alignment();

    bn::sprite_text_generator response_text_generator(common::fixed_8x16_sprite_font);
    response_text_generator.set_left_alignment();

    
    bn::vector<bn::sprite_ptr, 60> text_sprites;
    
    
    bn::sprite_ptr keyboard_pointer = bn::sprite_items::keyboard_ptr.create_sprite(0, 0);

    Keypad_Type last_pressed = NONE;
    
    int keyboard_pointer_x = 0;
    int keyboard_pointer_y = 0;
    
    bn::regular_bg_ptr green_bg = bn::regular_bg_items::green.create_bg(0, 0);
    bn::regular_bg_ptr keyboard_bg = bn::regular_bg_items::keyboard.create_bg(0, 0);
    
    bn::random random = bn::random();
    
    keyboard_bg.set_priority(1);
    keyboard_pointer.set_bg_priority(3);

    bn::string<60> out_message = "";
    bn::string<60> response_message = "";

    int response_state = USER_RESPONDING;
    

    while(true)
    {
        
        random.update();
                
        // response_text_generator.generate(-90, -75, out_message, text_sprites);
        int start_x = -90;
        int start_y = -75;
        int max_x = 90;
        int x = start_x;
        int y = start_y;
        
        if (response_state == USER_RESPONDING) {
            for (char c : out_message) {
                if (x >= max_x) {
                    x = start_x;
                    y += 16;
                }
                bn::string<1> char_text;
                bn::ostringstream text_stream(char_text);
                text_stream.append(c);
                
                response_text_generator.generate(x, y, char_text, text_sprites);
                x += 8;
            }
        } else {
            for (char c : response_message) {
                if (x >= max_x) {
                    x = start_x;
                    y += 16;
                }
                bn::string<1> char_text;
                bn::ostringstream text_stream(char_text);
                text_stream.append(c);
                
                response_text_generator.generate(x, y, char_text, text_sprites);
                x += 8;
            }
        }
        
        if (response_state == COMPUTER_RESPONDING) {
            
            bn::string add_to_response = build_response_message(out_message, response_message, random);
            
            if (add_to_response.empty()) {
                response_state = USER_WAITING;
                out_message.clear();
            } else {
                response_message.append(add_to_response);
            }
        }
        
        
        if (bn::keypad::a_held()) {
            if (last_pressed != A_BUTTON) {
                if (response_state == USER_RESPONDING) {
                    if (keyboard_pointer_x == 8 && keyboard_pointer_y == 2) {
                        if (out_message.length() > 0) {
                            out_message.pop_back();
                        }
                    } else if (keyboard_pointer_x == 9 && keyboard_pointer_y == 2) {
                        response_state = COMPUTER_RESPONDING;
                        
                    } else {
                        if (!out_message.full()) {
                            out_message = out_message + get_pointed_char(keyboard_pointer_x, keyboard_pointer_y);
                        }
                    }
                } else if (response_state == USER_WAITING) {
                    response_state = USER_RESPONDING;
                    response_message.clear();
                }
                last_pressed = A_BUTTON;
            }
        } else if (bn::keypad::right_held()) {
            if (last_pressed != RIGHT) {
                keyboard_pointer_x += 1;
                last_pressed = RIGHT;
            }
        } else if (bn::keypad::left_held()) {
            if (last_pressed != LEFT) {
                keyboard_pointer_x -= 1;
                last_pressed = LEFT;
            }
        } else if (bn::keypad::up_held()) {
            if (last_pressed != UP) {
                keyboard_pointer_y -= 1;
                last_pressed = UP;
            }
        } else if (bn::keypad::down_held()) {
            if (last_pressed != DOWN) {
                keyboard_pointer_y += 1;
                last_pressed = DOWN;
            }
        } else {
            last_pressed = NONE;
        }
        
        
        
        keyboard_pointer_x = keyboard_pointer_x < 10 ? keyboard_pointer_x : 9;
        keyboard_pointer_y = keyboard_pointer_y < 3 ? keyboard_pointer_y : 2;
        keyboard_pointer_x = keyboard_pointer_x >= 0 ? keyboard_pointer_x : 0;
        keyboard_pointer_y = keyboard_pointer_y >= 0 ? keyboard_pointer_y : 0;

        keyboard_pointer.set_position(keyboard_pointer_x*16-72 + keyboard_pointer_y*8, keyboard_pointer_y*16+32);
        
        bn::core::update();
        text_sprites.clear();

    }
}
