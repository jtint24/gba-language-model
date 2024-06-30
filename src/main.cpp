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
        if (computer_response_so_far.length() > 52) {
            return "";
        }
        
        bn::string<12> last_word;
        bn::ostringstream text_stream(last_word);

        for (int i = computer_response_so_far.length()-1; i>=0; i--) {
            if (computer_response_so_far.at(i) == ' ') {
                break;
            } else {
                text_stream.append(computer_response_so_far.at(i));
            }
        }
                
        /* START GENERATED CODE */
        if (last_word.length() == 0) {
            if (rand.get_unbiased_int(0, 40) == 0) return "hello" ;
            if (rand.get_unbiased_int(0, 39) == 0) return "hi" ;
            if (rand.get_unbiased_int(0, 38) == 0) return "hey" ;
            if (rand.get_unbiased_int(0, 37) == 0) return "good" ;
            if (rand.get_unbiased_int(0, 36) == 0) return "good" ;
            if (rand.get_unbiased_int(0, 35) == 0) return "good" ;
            if (rand.get_unbiased_int(0, 34) == 0) return "how" ;
            if (rand.get_unbiased_int(0, 33) == 0) return "hows" ;
            if (rand.get_unbiased_int(0, 32) == 0) return "whats" ;
            if (rand.get_unbiased_int(0, 31) == 0) return "howdy" ;
            if (rand.get_unbiased_int(0, 30) == 0) return "greetings" ;
            if (rand.get_unbiased_int(0, 29) == 0) return "nice" ;
            if (rand.get_unbiased_int(0, 28) == 0) return "how" ;
            if (rand.get_unbiased_int(0, 27) == 0) return "long" ;
            if (rand.get_unbiased_int(0, 26) == 0) return "whats" ;
            if (rand.get_unbiased_int(0, 25) == 0) return "hows" ;
            if (rand.get_unbiased_int(0, 24) == 0) return "hows" ;
            if (rand.get_unbiased_int(0, 23) == 0) return "its" ;
            if (rand.get_unbiased_int(0, 22) == 0) return "welcome" ;
            if (rand.get_unbiased_int(0, 21) == 0) return "hiya" ;
            if (rand.get_unbiased_int(0, 20) == 0) return "hi" ;
            if (rand.get_unbiased_int(0, 19) == 0) return "hello" ;
            if (rand.get_unbiased_int(0, 18) == 0) return "hey" ;
            if (rand.get_unbiased_int(0, 17) == 0) return "good" ;
            if (rand.get_unbiased_int(0, 16) == 0) return "hi" ;
            if (rand.get_unbiased_int(0, 15) == 0) return "hello" ;
            if (rand.get_unbiased_int(0, 14) == 0) return "hey" ;
            if (rand.get_unbiased_int(0, 13) == 0) return "good" ;
            if (rand.get_unbiased_int(0, 12) == 0) return "hi" ;
            if (rand.get_unbiased_int(0, 11) == 0) return "hello" ;
            if (rand.get_unbiased_int(0, 10) == 0) return "hey" ;
            if (rand.get_unbiased_int(0, 9) == 0) return "good" ;
            if (rand.get_unbiased_int(0, 8) == 0) return "hi" ;
            if (rand.get_unbiased_int(0, 7) == 0) return "hello" ;
            if (rand.get_unbiased_int(0, 6) == 0) return "hey" ;
            if (rand.get_unbiased_int(0, 5) == 0) return "good" ;
            if (rand.get_unbiased_int(0, 4) == 0) return "hi" ;
            if (rand.get_unbiased_int(0, 3) == 0) return "hello" ;
            if (rand.get_unbiased_int(0, 2) == 0) return "hey" ;
            if (rand.get_unbiased_int(0, 1) == 0) return "good" ;
        }
        if (last_word.at(0) == 'o') {
            if (last_word.at(1) == 'l') {
                if (last_word.at(2) == 'l') {
                    if (last_word.at(3) == 'e') {
                        if (last_word.at(4) == 'h') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 6) == 0) return "" ;
                                if (rand.get_unbiased_int(0, 5) == 0) return " what" ;
                                if (rand.get_unbiased_int(0, 4) == 0) return " hows" ;
                                if (rand.get_unbiased_int(0, 3) == 0) return " do" ;
                                if (rand.get_unbiased_int(0, 2) == 0) return " whats" ;
                                if (rand.get_unbiased_int(0, 1) == 0) return " how" ;
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 't') {
                if (last_word.length() == 2) {
                    if (rand.get_unbiased_int(0, 8) == 0) return " meet" ;
                    if (rand.get_unbiased_int(0, 7) == 0) return " see" ;
                    if (rand.get_unbiased_int(0, 6) == 0) return " lately" ;
                    if (rand.get_unbiased_int(0, 5) == 0) return " spend" ;
                    if (rand.get_unbiased_int(0, 4) == 0) return " make" ;
                    if (rand.get_unbiased_int(0, 3) == 0) return " unwind" ;
                    if (rand.get_unbiased_int(0, 2) == 0) return " any" ;
                    if (rand.get_unbiased_int(0, 1) == 0) return " stay" ;
                }
            }
            if (last_word.at(1) == 'n') {
                if (last_word.length() == 2) {
                    if (rand.get_unbiased_int(0, 1) == 0) return " see" ;
                }
            }
            if (last_word.at(1) == 'd') {
                if (last_word.length() == 2) {
                    if (rand.get_unbiased_int(0, 3) == 0) return " you" ;
                    if (rand.get_unbiased_int(0, 2) == 0) return " you" ;
                    if (rand.get_unbiased_int(0, 1) == 0) return " you" ;
                }
            }
        }
        if (last_word.at(0) == 'i') {
            if (last_word.at(1) == 'h') {
                if (last_word.length() == 2) {
                    if (rand.get_unbiased_int(0, 6) == 0) return "" ;
                    if (rand.get_unbiased_int(0, 5) == 0) return " hows" ;
                    if (rand.get_unbiased_int(0, 4) == 0) return " there" ;
                    if (rand.get_unbiased_int(0, 3) == 0) return " whats" ;
                    if (rand.get_unbiased_int(0, 2) == 0) return " there" ;
                    if (rand.get_unbiased_int(0, 1) == 0) return " do" ;
                }
            }
        }
        if (last_word.at(0) == 'y') {
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 'h') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 6) == 0) return "" ;
                        if (rand.get_unbiased_int(0, 5) == 0) return " do" ;
                        if (rand.get_unbiased_int(0, 4) == 0) return " have" ;
                        if (rand.get_unbiased_int(0, 3) == 0) return " hows" ;
                        if (rand.get_unbiased_int(0, 2) == 0) return " do" ;
                        if (rand.get_unbiased_int(0, 1) == 0) return " have" ;
                    }
                }
            }
            if (last_word.at(1) == 'd') {
                if (last_word.at(2) == 'w') {
                    if (last_word.at(3) == 'o') {
                        if (last_word.at(4) == 'h') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'a') {
                if (last_word.at(2) == 'd') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 4) == 0) return " going" ;
                        if (rand.get_unbiased_int(0, 3) == 0) return " going" ;
                        if (rand.get_unbiased_int(0, 2) == 0) return " off" ;
                        if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                    }
                }
                if (last_word.at(2) == 'w') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 2) == 0) return " to" ;
                        if (rand.get_unbiased_int(0, 1) == 0) return " to" ;
                    }
                }
                if (last_word.at(2) == 't') {
                    if (last_word.at(3) == 's') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " active" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 'l') {
                if (last_word.at(2) == 'e') {
                    if (last_word.at(3) == 't') {
                        if (last_word.at(4) == 'a') {
                            if (last_word.at(5) == 'l') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 3) == 0) return "" ;
                                    if (rand.get_unbiased_int(0, 2) == 0) return "" ;
                                    if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                                }
                            }
                        }
                    }
                }
                if (last_word.at(2) == 't') {
                    if (last_word.at(3) == 'n') {
                        if (last_word.at(4) == 'e') {
                            if (last_word.at(5) == 'c') {
                                if (last_word.at(6) == 'e') {
                                    if (last_word.at(7) == 'r') {
                                        if (last_word.length() == 8) {
                                            if (rand.get_unbiased_int(0, 3) == 0) return "" ;
                                            if (rand.get_unbiased_int(0, 2) == 0) return "" ;
                                            if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'm') {
                        if (last_word.at(4) == 'a') {
                            if (last_word.at(5) == 'f') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return " doing" ;
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'n') {
                if (last_word.at(2) == 'a') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 7) == 0) return " plans" ;
                        if (rand.get_unbiased_int(0, 6) == 0) return " good" ;
                        if (rand.get_unbiased_int(0, 5) == 0) return " new" ;
                        if (rand.get_unbiased_int(0, 4) == 0) return " hobbies" ;
                        if (rand.get_unbiased_int(0, 3) == 0) return " sports" ;
                        if (rand.get_unbiased_int(0, 2) == 0) return " travel" ;
                        if (rand.get_unbiased_int(0, 1) == 0) return " fun" ;
                    }
                }
            }
        }
        if (last_word.at(0) == 'd') {
            if (last_word.at(1) == 'o') {
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'g') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 2) == 0) return " to" ;
                            if (rand.get_unbiased_int(0, 1) == 0) return " movies" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 'n') {
                if (last_word.at(2) == 'e') {
                    if (last_word.at(3) == 'k') {
                        if (last_word.at(4) == 'e') {
                            if (last_word.at(5) == 'e') {
                                if (last_word.at(6) == 'w') {
                                    if (last_word.length() == 7) {
                                        if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                                    }
                                }
                            }
                        }
                    }
                    if (last_word.at(3) == 'p') {
                        if (last_word.at(4) == 's') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return " a" ;
                            }
                        }
                    }
                }
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'w') {
                        if (last_word.at(4) == 'n') {
                            if (last_word.at(5) == 'u') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return " after" ;
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'i') {
                if (last_word.at(2) == 'd') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 1) == 0) return " you" ;
                    }
                }
            }
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'r') {
                        if (last_word.at(4) == 't') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return " any" ;
                            }
                        }
                    }
                }
                if (last_word.at(2) == 'n') {
                    if (last_word.at(3) == 'r') {
                        if (last_word.at(4) == 'a') {
                            if (last_word.at(5) == 'e') {
                                if (last_word.at(6) == 'l') {
                                    if (last_word.length() == 7) {
                                        if (rand.get_unbiased_int(0, 1) == 0) return " recently" ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'a') {
                if (last_word.at(2) == 'e') {
                    if (last_word.at(3) == 'r') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " recently" ;
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 'g') {
            if (last_word.at(1) == 'n') {
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'n') {
                        if (last_word.at(4) == 'r') {
                            if (last_word.at(5) == 'o') {
                                if (last_word.at(6) == 'm') {
                                    if (last_word.length() == 7) {
                                        if (rand.get_unbiased_int(0, 3) == 0) return "" ;
                                        if (rand.get_unbiased_int(0, 2) == 0) return " how" ;
                                        if (rand.get_unbiased_int(0, 1) == 0) return " whats" ;
                                    }
                                }
                            }
                        }
                        if (last_word.at(4) == 'e') {
                            if (last_word.at(5) == 'v') {
                                if (last_word.at(6) == 'e') {
                                    if (last_word.length() == 7) {
                                        if (rand.get_unbiased_int(0, 2) == 0) return "" ;
                                        if (rand.get_unbiased_int(0, 1) == 0) return " whats" ;
                                    }
                                }
                            }
                        }
                    }
                    if (last_word.at(3) == 'o') {
                        if (last_word.at(4) == 'g') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 3) == 0) return "" ;
                                if (rand.get_unbiased_int(0, 2) == 0) return "" ;
                                if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                            }
                        }
                        if (last_word.at(4) == 'd') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                            }
                        }
                    }
                    if (last_word.at(3) == 'h') {
                        if (last_word.at(4) == 't') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return " youve" ;
                            }
                        }
                    }
                    if (last_word.at(3) == 't') {
                        if (last_word.at(4) == 's') {
                            if (last_word.at(5) == 'e') {
                                if (last_word.at(6) == 'r') {
                                    if (last_word.at(7) == 'e') {
                                        if (last_word.at(8) == 't') {
                                            if (last_word.at(9) == 'n') {
                                                if (last_word.at(10) == 'i') {
                                                    if (last_word.length() == 11) {
                                                        if (rand.get_unbiased_int(0, 1) == 0) return " thing" ;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (last_word.at(3) == 'm') {
                        if (last_word.at(4) == 'o') {
                            if (last_word.at(5) == 'c') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return " up" ;
                                }
                            }
                        }
                    }
                    if (last_word.at(3) == 'k') {
                        if (last_word.at(4) == 'o') {
                            if (last_word.at(5) == 'o') {
                                if (last_word.at(6) == 'c') {
                                    if (last_word.length() == 7) {
                                        if (rand.get_unbiased_int(0, 1) == 0) return " whats" ;
                                    }
                                }
                            }
                        }
                    }
                }
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'l') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " day" ;
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 'n') {
            if (last_word.at(1) == 'o') {
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'n') {
                        if (last_word.at(4) == 'r') {
                            if (last_word.at(5) == 'e') {
                                if (last_word.at(6) == 't') {
                                    if (last_word.at(7) == 'f') {
                                        if (last_word.at(8) == 'a') {
                                            if (last_word.length() == 9) {
                                                if (rand.get_unbiased_int(0, 3) == 0) return "" ;
                                                if (rand.get_unbiased_int(0, 2) == 0) return " have" ;
                                                if (rand.get_unbiased_int(0, 1) == 0) return " whats" ;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 'e') {
                    if (last_word.at(3) == 'b') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 4) == 0) return "" ;
                            if (rand.get_unbiased_int(0, 3) == 0) return " up" ;
                            if (rand.get_unbiased_int(0, 2) == 0) return "" ;
                            if (rand.get_unbiased_int(0, 1) == 0) return " to" ;
                        }
                    }
                    if (last_word.at(3) == 's') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " any" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 'u') {
                if (last_word.at(2) == 'f') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 1) == 0) return " events" ;
                    }
                }
            }
        }
        if (last_word.at(0) == 'w') {
            if (last_word.at(1) == 'o') {
                if (last_word.at(2) == 'h') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 4) == 0) return " are" ;
                        if (rand.get_unbiased_int(0, 3) == 0) return " have" ;
                        if (rand.get_unbiased_int(0, 2) == 0) return " did" ;
                        if (rand.get_unbiased_int(0, 1) == 0) return " do" ;
                    }
                }
                if (last_word.at(2) == 'l') {
                    if (last_word.at(3) == 'l') {
                        if (last_word.at(4) == 'o') {
                            if (last_word.at(5) == 'f') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return " any" ;
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 'n') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 3) == 0) return "" ;
                        if (rand.get_unbiased_int(0, 2) == 0) return " with" ;
                        if (rand.get_unbiased_int(0, 1) == 0) return " restaurants" ;
                    }
                }
            }
        }
        if (last_word.at(0) == 'e') {
            if (last_word.at(1) == 'r') {
                if (last_word.at(2) == 'a') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 1) == 0) return " you" ;
                    }
                }
                if (last_word.at(2) == 'e') {
                    if (last_word.at(3) == 'h') {
                        if (last_word.at(4) == 't') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 2) == 0) return " whats" ;
                                if (rand.get_unbiased_int(0, 1) == 0) return " do" ;
                            }
                        }
                    }
                }
                if (last_word.at(2) == 'u') {
                    if (last_word.at(3) == 'o') {
                        if (last_word.at(4) == 'y') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return " passionate" ;
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'c') {
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'n') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " to" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 'v') {
                if (last_word.at(2) == 'a') {
                    if (last_word.at(3) == 'h') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " you" ;
                        }
                    }
                }
                if (last_word.at(2) == 'u') {
                    if (last_word.at(3) == 'o') {
                        if (last_word.at(4) == 'y') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 2) == 0) return " read" ;
                                if (rand.get_unbiased_int(0, 1) == 0) return " learned" ;
                            }
                        }
                    }
                }
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 't') {
                        if (last_word.at(4) == 'c') {
                            if (last_word.at(5) == 'a') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'm') {
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 't') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " no" ;
                        }
                    }
                }
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'c') {
                        if (last_word.at(4) == 'l') {
                            if (last_word.at(5) == 'e') {
                                if (last_word.at(6) == 'w') {
                                    if (last_word.length() == 7) {
                                        if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 's') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 2) == 0) return "" ;
                        if (rand.get_unbiased_int(0, 1) == 0) return " you" ;
                    }
                }
            }
            if (last_word.at(1) == 'h') {
                if (last_word.at(2) == 't') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 3) == 0) return " weekend" ;
                        if (rand.get_unbiased_int(0, 2) == 0) return " best" ;
                        if (rand.get_unbiased_int(0, 1) == 0) return " most" ;
                    }
                }
            }
            if (last_word.at(1) == 't') {
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'r') {
                        if (last_word.at(4) == 'o') {
                            if (last_word.at(5) == 'v') {
                                if (last_word.at(6) == 'a') {
                                    if (last_word.at(7) == 'f') {
                                        if (last_word.length() == 8) {
                                            if (rand.get_unbiased_int(0, 4) == 0) return " way" ;
                                            if (rand.get_unbiased_int(0, 3) == 0) return " type" ;
                                            if (rand.get_unbiased_int(0, 2) == 0) return " dish" ;
                                            if (rand.get_unbiased_int(0, 1) == 0) return " way" ;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (last_word.at(2) == 'a') {
                    if (last_word.at(3) == 'n') {
                        if (last_word.at(4) == 'o') {
                            if (last_word.at(5) == 'i') {
                                if (last_word.at(6) == 's') {
                                    if (last_word.at(7) == 's') {
                                        if (last_word.at(8) == 'a') {
                                            if (last_word.at(9) == 'p') {
                                                if (last_word.length() == 10) {
                                                    if (rand.get_unbiased_int(0, 1) == 0) return " about" ;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'p') {
                if (last_word.at(2) == 'y') {
                    if (last_word.at(3) == 't') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " of" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 'k') {
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'l') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 2) == 0) return " cooking" ;
                            if (rand.get_unbiased_int(0, 1) == 0) return " to" ;
                        }
                    }
                }
                if (last_word.at(2) == 'a') {
                    if (last_word.at(3) == 'm') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 'u') {
            if (last_word.at(1) == 'o') {
                if (last_word.at(2) == 'y') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 16) == 0) return "" ;
                        if (rand.get_unbiased_int(0, 15) == 0) return "" ;
                        if (rand.get_unbiased_int(0, 14) == 0) return " been" ;
                        if (rand.get_unbiased_int(0, 13) == 0) return "" ;
                        if (rand.get_unbiased_int(0, 12) == 0) return " been" ;
                        if (rand.get_unbiased_int(0, 11) == 0) return " have" ;
                        if (rand.get_unbiased_int(0, 10) == 0) return " sleep" ;
                        if (rand.get_unbiased_int(0, 9) == 0) return "" ;
                        if (rand.get_unbiased_int(0, 8) == 0) return " seen" ;
                        if (rand.get_unbiased_int(0, 7) == 0) return " tried" ;
                        if (rand.get_unbiased_int(0, 6) == 0) return " have" ;
                        if (rand.get_unbiased_int(0, 5) == 0) return " follow" ;
                        if (rand.get_unbiased_int(0, 4) == 0) return " have" ;
                        if (rand.get_unbiased_int(0, 3) == 0) return " like" ;
                        if (rand.get_unbiased_int(0, 2) == 0) return " like" ;
                        if (rand.get_unbiased_int(0, 1) == 0) return " been" ;
                    }
                }
            }
        }
        if (last_word.at(0) == 's') {
            if (last_word.at(1) == 'w') {
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'h') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 2) == 0) return " your" ;
                            if (rand.get_unbiased_int(0, 1) == 0) return " your" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 't') {
                if (last_word.at(2) == 'a') {
                    if (last_word.at(3) == 'h') {
                        if (last_word.at(4) == 'w') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 9) == 0) return " up" ;
                                if (rand.get_unbiased_int(0, 8) == 0) return " new" ;
                                if (rand.get_unbiased_int(0, 7) == 0) return " new" ;
                                if (rand.get_unbiased_int(0, 6) == 0) return " your" ;
                                if (rand.get_unbiased_int(0, 5) == 0) return " the" ;
                                if (rand.get_unbiased_int(0, 4) == 0) return " the" ;
                                if (rand.get_unbiased_int(0, 3) == 0) return " your" ;
                                if (rand.get_unbiased_int(0, 2) == 0) return " your" ;
                                if (rand.get_unbiased_int(0, 1) == 0) return " your" ;
                            }
                        }
                    }
                }
                if (last_word.at(2) == 'i') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 1) == 0) return " good" ;
                    }
                }
                if (last_word.at(2) == 'n') {
                    if (last_word.at(3) == 'a') {
                        if (last_word.at(4) == 'r') {
                            if (last_word.at(5) == 'u') {
                                if (last_word.at(6) == 'a') {
                                    if (last_word.at(7) == 't') {
                                        if (last_word.at(8) == 's') {
                                            if (last_word.at(9) == 'e') {
                                                if (last_word.at(10) == 'r') {
                                                    if (last_word.length() == 11) {
                                                        if (rand.get_unbiased_int(0, 1) == 0) return " lately" ;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (last_word.at(3) == 'e') {
                        if (last_word.at(4) == 'v') {
                            if (last_word.at(5) == 'e') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return " lately" ;
                                }
                            }
                        }
                    }
                }
                if (last_word.at(2) == 'r') {
                    if (last_word.at(3) == 'o') {
                        if (last_word.at(4) == 'p') {
                            if (last_word.at(5) == 's') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return " teams" ;
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'g') {
                if (last_word.at(2) == 'n') {
                    if (last_word.at(3) == 'i') {
                        if (last_word.at(4) == 't') {
                            if (last_word.at(5) == 'e') {
                                if (last_word.at(6) == 'e') {
                                    if (last_word.at(7) == 'r') {
                                        if (last_word.at(8) == 'g') {
                                            if (last_word.length() == 9) {
                                                if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'n') {
                if (last_word.at(2) == 'a') {
                    if (last_word.at(3) == 'l') {
                        if (last_word.at(4) == 'p') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 2) == 0) return " for" ;
                                if (rand.get_unbiased_int(0, 1) == 0) return " coming" ;
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'v') {
                        if (last_word.at(4) == 'o') {
                            if (last_word.at(5) == 'm') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return " recently" ;
                                }
                            }
                        }
                    }
                    if (last_word.at(3) == 'b') {
                        if (last_word.at(4) == 'b') {
                            if (last_word.at(5) == 'o') {
                                if (last_word.at(6) == 'h') {
                                    if (last_word.length() == 7) {
                                        if (rand.get_unbiased_int(0, 1) == 0) return " youre" ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'm') {
                if (last_word.at(2) == 'a') {
                    if (last_word.at(3) == 'e') {
                        if (last_word.at(4) == 't') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                            }
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 't') {
            if (last_word.at(1) == 'i') {
                if (last_word.length() == 2) {
                    if (rand.get_unbiased_int(0, 1) == 0) return " going" ;
                }
            }
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 'e') {
                    if (last_word.at(3) == 'm') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " you" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 'a') {
                if (last_word.at(2) == 'h') {
                    if (last_word.at(3) == 'w') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " have" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 'u') {
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'b') {
                        if (last_word.at(4) == 'a') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 's') {
                if (last_word.at(2) == 'e') {
                    if (last_word.at(3) == 'b') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " book" ;
                        }
                    }
                }
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'm') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " interesting" ;
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 'p') {
            if (last_word.at(1) == 'u') {
                if (last_word.length() == 2) {
                    if (rand.get_unbiased_int(0, 3) == 0) return "" ;
                    if (rand.get_unbiased_int(0, 2) == 0) return " to" ;
                    if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                }
            }
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 'e') {
                    if (last_word.at(3) == 'l') {
                        if (last_word.at(4) == 's') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                            }
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 'r') {
            if (last_word.at(1) == 'u') {
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'y') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 7) == 0) return " day" ;
                            if (rand.get_unbiased_int(0, 6) == 0) return " day" ;
                            if (rand.get_unbiased_int(0, 5) == 0) return " favorite" ;
                            if (rand.get_unbiased_int(0, 4) == 0) return " family" ;
                            if (rand.get_unbiased_int(0, 3) == 0) return " favorite" ;
                            if (rand.get_unbiased_int(0, 2) == 0) return " favorite" ;
                            if (rand.get_unbiased_int(0, 1) == 0) return " favorite" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 'o') {
                if (last_word.length() == 2) {
                    if (rand.get_unbiased_int(0, 1) == 0) return " school" ;
                }
            }
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 't') {
                    if (last_word.at(3) == 'f') {
                        if (last_word.at(4) == 'a') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return " a" ;
                            }
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 'a') {
            if (last_word.length() == 1) {
                if (rand.get_unbiased_int(0, 2) == 0) return " day" ;
                if (rand.get_unbiased_int(0, 1) == 0) return " long" ;
            }
        }
        if (last_word.at(0) == 'h') {
            if (last_word.at(1) == 't') {
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'w') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " you" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 's') {
                if (last_word.at(2) == 'i') {
                    if (last_word.at(3) == 'd') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " to" ;
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 'k') {
            if (last_word.at(1) == 'r') {
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'w') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " or" ;
                        }
                    }
                }
            }
            if (last_word.at(1) == 'o') {
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'b') {
                        if (last_word.length() == 4) {
                            if (rand.get_unbiased_int(0, 1) == 0) return " youve" ;
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 'l') {
            if (last_word.at(1) == 'o') {
                if (last_word.at(2) == 'o') {
                    if (last_word.at(3) == 'h') {
                        if (last_word.at(4) == 'c') {
                            if (last_word.at(5) == 's') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return " been" ;
                                }
                            }
                        }
                    }
                }
            }
            if (last_word.at(1) == 'e') {
                if (last_word.at(2) == 'v') {
                    if (last_word.at(3) == 'a') {
                        if (last_word.at(4) == 'r') {
                            if (last_word.at(5) == 't') {
                                if (last_word.length() == 6) {
                                    if (rand.get_unbiased_int(0, 1) == 0) return " plans" ;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (last_word.at(0) == 'f') {
            if (last_word.at(1) == 'f') {
                if (last_word.at(2) == 'o') {
                    if (last_word.length() == 3) {
                        if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                    }
                }
            }
            if (last_word.at(1) == 'o') {
                if (last_word.length() == 2) {
                    if (rand.get_unbiased_int(0, 1) == 0) return " music" ;
                }
            }
        }
        if (last_word.at(0) == 'c') {
            if (last_word.at(1) == 'i') {
                if (last_word.at(2) == 's') {
                    if (last_word.at(3) == 'u') {
                        if (last_word.at(4) == 'm') {
                            if (last_word.length() == 5) {
                                if (rand.get_unbiased_int(0, 1) == 0) return "" ;
                            }
                        }
                    }
                }
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
