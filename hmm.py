import random
import string
from typing import List, Dict, Tuple, Counter, Set
from datasets import load_dataset
from unidecode import unidecode

dataset = load_dataset("AlderleyAI/coqa_chat", "default")


class PrefixTreeNode:
    def __init__(self, payload: List[str]):
        self.children = {}
        self.payload = payload

    def add_child_single(self, char: str, payload: List[str]):
        self.children[char] = PrefixTreeNode(payload)

    def add_child(self, key: str, payload: List[str]):
        if len(key) == 0:
            self.payload += payload
        else:
            if key[0] not in self.children:
                self.children[key[0]] = PrefixTreeNode([])
            self.children[key[0]].add_child(key[1:], payload)

    def hierarchical_rep(self, level: int = 0) -> str:
        return (" "*level) + "- " + str(self.payload) + "\n" + "\n".join([child.hierarchical_rep(level+1) for key, child in self.children.items()])

    def __repr__(self) -> str:
        #return self.hierarchical_rep()
        return "PrefixTreeNode()"

    def to_cpp_code(self, var: str, word_mapping: Dict[str, Dict[str, int]], level: int = 0, key_str: str = "") -> str:
        body = ""

        if len(self.payload) > 0:
            if len(self.payload) > 100:
                self.payload = random.sample(self.payload, 100)
            if all(i == self.payload[0] for i in self.payload):
                self.payload = [self.payload[0]]
            body += ("\t"*level) + "if ("+var+".length() == "+str(level)+") {\n"
            count = len(self.payload)
            for word in self.payload:
                top_words_condition = ""
                iterate_top_words = word_mapping[word.strip()].items()
                if len(iterate_top_words) > 5:
                    iterate_top_words = sorted(iterate_top_words, key=lambda pair: pair[1])[-5:]
                for top_word, top_word_count in iterate_top_words:
                    if top_word_count > 2:
                        top_words_condition += " || "
                        top_words_condition += '(prompt_words.contains("'+top_word+'") && rand.get_unbiased_int(0, '+str(round(top_word_count+count//20))+') < '+str(round(top_word_count))+')'
                if not is_function_word(word):
                    top_words_condition += '|| (prompt_words.contains("'+word.strip()+'"))'
                body += ("\t"*level) + "\tif (rand.get_unbiased_int(0, "+str(count)+') == 0 '+top_words_condition+') return "' + word + '" ;\n'
                count -= 1
            body += ("\t"*level) + "}\n"

        for key, child in self.children.items():
            body += ("\t"*level) + "if ("+var+".at("+str(level)+") == '"+key+"') {\n"
            body += child.to_cpp_code(var, word_mapping, level=level+1, key_str=key+key_str)
            body += ("\t"*level) + "}\n"

        return body


def add_top_word_counters(top_word_counters: List[Dict[str, int]]) -> Dict[str, int]:
    keys = set().union(*[top_word_counter.keys() for top_word_counter in top_word_counters])
    return {
        key: sum([word_counter.get(key, 0) for word_counter in top_word_counters])
        for key
        in keys
    }


def halve_top_word_counter(top_word_counter: Dict[str, int]) -> Dict[str, int]:
    return {
        key: value/2
        for key, value
        in top_word_counter.items()
    }




def get_top_words(word_mapping: Dict[str, int]) -> Set[str]:
    total_count = sum([count for word, count in word_mapping.items()])
    top_words = set()
    for word, count in word_mapping.items():
        if count > 1 and count >= 0.02 * total_count:
            top_words.add(word)
    return top_words

def is_function_word(word: str) -> bool:
    function_words = {"a", "about", "above", "across", "after", "afterwards", "again", "against", "all", "almost", "alone", "along", "already", "also", "although", "always", "am", "among", "amongst", "amoungst", "an", "and", "another", "any", "anyhow", "anyone", "anything", "anyway", "anywhere", "are", "around", "as", "at", "be", "became", "because", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", "beyond", "both", "but", "by", "can", "cannot", "could", "dare", "despite", "did", "do", "does", "done", "down", "during", "each", "eg", "either", "else", "elsewhere", "enough", "etc", "even", "ever", "every", "everyone", "everything", "everywhere", "except", "few", "first", "for", "former", "formerly", "from", "further", "furthermore", "had", "has", "have", "he", "hence", "her", "here", "hereabouts", "hereafter", "hereby", "herein", "hereinafter", "heretofore", "hereunder", "hereupon", "herewith", "hers", "herself", "him", "himself", "his", "how", "however", "i", "ie", "if", "in", "indeed", "inside", "instead", "into", "is", "it", "its", "itself", "last", "latter", "latterly", "least", "less", "lot", "lots", "many", "may", "me", "meanwhile", "might", "mine", "more", "moreover", "most", "mostly", "much", "must", "my", "myself", "namely", "near", "need", "neither", "never", "nevertheless", "next", "no", "nobody", "none", "noone", "nor", "not", "nothing", "now", "nowhere", "of", "off", "often", "oftentimes", "on", "once", "one", "only", "onto", "or", "other", "others", "otherwise", "ought", "our", "ours", "ourselves", "out", "outside", "over", "per", "perhaps", "rather", "re", "same", "second", "several", "shall", "she", "should", "since", "so", "some", "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "still", "such", "than", "that", "the", "their", "theirs", "them", "themselves", "then", "thence", "there", "thereabouts", "thereafter", "thereby", "therefore", "therein", "thereof", "thereon", "thereupon", "these", "they", "third", "this", "those", "though", "through", "throughout", "thru", "thus", "to", "together", "too", "top", "toward", "towards", "under", "until", "up", "upon", "us", "used", "very", "via", "was", "we", "well", "were", "what", "whatever", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "whereupon", "wherever", "whether", "which", "while", "whither", "who", "whoever", "whole", "whom", "whose", "why", "whyever", "will", "with", "within", "without", "would", "yes", "yet", "you", "your", "yours", "yourself", "yourselves"}
    return word in function_words

def generate_markov_dict(texts: List[Tuple[str, str]]) -> Tuple[Dict[str, List[str]], Dict[str, Dict[str, int]]]:
    markov_dict = {}
    word_mapping = {}

    for question, answer in texts:
        cleaned_punctuation_answer = answer.lower().translate(str.maketrans('', '', string.punctuation))
        cleaned_punctuation_answer = cleaned_punctuation_answer.replace("’", "")
        cleaned_punctuation_question = question.lower().translate(str.maketrans('', '', string.punctuation))
        cleaned_punctuation_question = cleaned_punctuation_question.replace("’", "")

        answer_words = cleaned_punctuation_answer.split(" ")
        question_words = cleaned_punctuation_question.split(" ")

        for answer_word in answer_words:
            if answer_word not in word_mapping:
                word_mapping[answer_word] = {}
            for question_word in question_words:
                if not is_function_word(question_word):
                    if question_word not in word_mapping[answer_word]:
                        word_mapping[answer_word][question_word] = 0
                    word_mapping[answer_word][question_word] += 1

        # if prompt_words.contains(QUESTION WORD) give ANSWER WORD

        answer_words = ["", ""] + answer_words + [""]

        for word1, word2, word3 in zip(answer_words, answer_words[1:], answer_words[2:]):
            key = word1+" "+word2
            if key not in markov_dict:
                markov_dict[key] = []
            markov_dict[key].append(word3)

    return (markov_dict, word_mapping)

def get_text_from_dataset() -> List[Tuple[str, str]]:
    n = 0
    max_n = 300

    out_data = []
    for row in dataset["train"].to_iterable_dataset():
        if n % 10 == 0:
            pass
            # print(n, len(out_data))
        text = (row["question"], row["answer"])
        out_data.append(text)
        n += 1
        if n == max_n:
            break
    return out_data

def main():
    ptn = PrefixTreeNode([])

    texts = get_text_from_dataset()
    # print(texts)

    markov_dict, qa_mapping = generate_markov_dict(texts)

    for word, next_words in markov_dict.items():
        for next_word in next_words:
            if word in qa_mapping:
                total_top_words = add_top_word_counters([qa_mapping[next_word], qa_mapping[word]])
                qa_mapping[word] = total_top_words
    # print(qa_mapping)

    for word, payload in markov_dict.items():
        processed_payload = [unidecode(w.lower()) for w in payload] if len(word) == 0 else [" "+unidecode(w.lower()) if len(w)>0 else "" for w in payload]
        ptn.add_child(unidecode(word).lower()[::-1], processed_payload)
    # print(ptn.children['e'].children['h'].children['t'])
    print(
        """
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
        """
    )
    print("bn::string<60> build_generated_message(bn::string<60> out_message, bn::string<60> last_word, bn::random rand) {")
    print("""
    bn::string<60> current_word;
    bn::unordered_set<bn::string_view, 256> prompt_words;
    bn::vector<bn::string_view, 60> ordered_words;
    for (char c : out_message) {
        if (c == ' ' || c == '?') {
            ordered_words.push_back(bn::string(current_word));
            prompt_words.insert(bn::string(current_word));

            current_word.assign("");
        } else {
            current_word += c;
        }
    }
    if (!current_word.empty()) {
        prompt_words.insert(current_word);
        ordered_words.push_back(current_word);
    }""")
    print(
        """
        BN_LOG("Outside pattern check");
        if (ordered_words.size() > 2 && (out_message.starts_with("what is") || out_message.starts_with("why is") || out_message.starts_with("how is")) && last_word.size() < 2) {
            BN_LOG("Inside patte it check");
            if (ordered_words[2] == bn::string<60>("the")) {
                BN_LOG("It's a 'the' phrase");
                // int size = ordered_words[2].length()+ordered_words[3].length()+5;
                return bn::string<30>("the ") + ordered_words[3] + bn::string<30>(" is");
            } else {
                return ordered_words[2]+bn::string<30>(" is");
            }
        }
        """
    )
    print(ptn.to_cpp_code("last_word", qa_mapping, level=0))
    print("\treturn \"\";")
    print("}")





if __name__=="__main__":
    main()


