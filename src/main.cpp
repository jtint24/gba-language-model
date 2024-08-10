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
#include "bn_unordered_set.h"

#include "bn_sprite_items_keyboard_ptr.h"
#include "bn_sprite_items_keyboard_bg.h"
#include "bn_regular_bg_items_send_chat.h"
#include "bn_regular_bg_items_recv_chat.h"
#include "bn_regular_bg_items_chat_wait.h"
#include "bn_regular_bg_items_green.h"
#include "bn_regular_bg_items_keyboard.h"
#include "bn_sprite_items_backspace.h"
#include "bn_sprite_items_enter.h"
#include "bn_sprite_items_space.h"
#include "bn_sprite_items_fixed_8x16_font.h"
#include "fixed_32x64_sprite_font.h"


#include "build_generated_message.cpp"
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
    

//bn::string<60> build_generated_message(bn::string<60> out_message, bn::string<60> last_word, bn::random rand) {
//    
//    bn::string<60> current_word;
//    bn::unordered_set<bn::string_view, 256> prompt_words;
//    bn::vector<bn::string_view, 60> ordered_words;
//    for (char c : out_message) {
//        if (c == ' ' || c == '?') {
//            ordered_words.push_back(bn::string(current_word));
//            prompt_words.insert(bn::string(current_word));
//            
//            current_word.assign("");
//        } else {
//            current_word += c;
//        }
//    }
//    if (!current_word.empty()) {
//        prompt_words.insert(current_word);
//        ordered_words.push_back(current_word);
//    }
//    
//    // BN_LOG("Outside pattern check");
//    if (ordered_words.size() > 2 && (out_message.starts_with("what is") || out_message.starts_with("why is") || out_message.starts_with("how is")) && last_word.size() < 2) {
//         BN_LOG("Inside patte it check");
//        if (ordered_words[2] == "the") {
//            return ordered_words[2]+bn::string<60>(" ") + ordered_words[3] + bn::string<60>(" is");
//        } else {
//            return ordered_words[2]+bn::string<60>(" is");
//        }
//    }
//    
//    return "";
//}

    
    bn::string<60> build_response_message(bn::string<60> out_message, bn::string<60> computer_response_so_far, bn::random rand) {
        BN_LOG("out_message", out_message);
        if (out_message.empty()) {
            return "sorry i didnt get that";
        }
        if (computer_response_so_far.length() > 55) {
            return "";
        }
        
        bn::string<60> last_word;
        bn::ostringstream text_stream(last_word);
        int space_count = 0;
        
        for (int i = computer_response_so_far.length()-1; i>=0; i--) {
            if (computer_response_so_far.at(i) == ' ') {
                space_count++;
                if (space_count == 2) {
                    break;
                }
            }
            text_stream.append(computer_response_so_far.at(i));
            
        }
        
        if (last_word.length() == 0) {
            last_word += " ";
        }
                
        return build_generated_message(out_message, last_word, rand);
    }


template <typename T>
bn::string<255> pretty(const T& container) {
    bn::string<255> result;
    bn::ostringstream oss(result);
    bool first_element_written = false;
    oss << ".[";
    for (const auto& element : container) {
        if (!first_element_written) {
            oss << element;
            first_element_written = true;
        } else {
            oss << ", " << element;
        }
    }
    oss << "].";
    return result;
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
    
    // bn::regular_bg_ptr green_bg = bn::regular_bg_items::green.create_bg(0, 0);
    bn::regular_bg_ptr keyboard_bg = bn::regular_bg_items::keyboard.create_bg(0, 0);
    bn::regular_bg_ptr send_chat_bg = bn::regular_bg_items::send_chat.create_bg(0, 0);
    bn::regular_bg_ptr recv_chat_bg = bn::regular_bg_items::recv_chat.create_bg(0, 0);
    bn::regular_bg_ptr chat_wait_bg = bn::regular_bg_items::chat_wait.create_bg(0, 0);

    bn::random random = bn::random();
    
    keyboard_bg.set_priority(1);
    keyboard_pointer.set_bg_priority(3);

    bn::string<60> out_message = "";
    bn::string<60> response_message = "";
    bn::unordered_set<bn::string_view, 512> word_set;


    int response_state = USER_RESPONDING;
    

    while(true)
    {
        
        random.update();
        
        send_chat_bg.set_visible(response_state == USER_RESPONDING);
        recv_chat_bg.set_visible(response_state == COMPUTER_RESPONDING);
        chat_wait_bg.set_visible(response_state == USER_WAITING);

                
        int start_x = -90;
        int start_y = -70;
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
            BN_LOG("re-responding");
            
            BN_LOG("PRE IN PROMPT WORDS: ",pretty(word_set));

            
            bn::string add_to_response = build_response_message(out_message, response_message, random);
            BN_LOG("length: ");
            BN_LOG(add_to_response.length());
            BN_LOG("available: ");
            BN_LOG(response_message.available());
            BN_LOG(add_to_response);
            BN_LOG(response_message);
            BN_LOG("add to response: '", add_to_response, "'");
            

            if (add_to_response == bn::string<60>("sorry i didnt get that")) {
                response_message.append(add_to_response);
                response_state = USER_WAITING;
                out_message.clear();

            } else if (add_to_response.empty() || response_message.available() <= add_to_response.length()) {
                response_state = USER_WAITING;
                out_message.clear();
            } else {
                response_message.append(add_to_response);
                BN_LOG("done");
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
                        word_set.clear();
                        
                    
                        
                        
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

