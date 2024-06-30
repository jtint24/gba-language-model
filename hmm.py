import random
import string
from typing import List, Dict
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
        return self.hierarchical_rep()

    def to_cpp_code(self, var: str, level: int = 0) -> str:
        body = ""
        if len(self.payload) > 0:
            body += ("\t"*level) + "if ("+var+".length() == "+str(level)+") {\n"
            count = len(self.payload)
            for word in self.payload:
                body += ("\t"*level) + "\tif (rand.get_unbiased_int(0, "+str(count)+') == 0) return "' + word + '" ;\n'
                count -= 1
            body += ("\t"*level) + "}\n"
        for key, value in self.children.items():
            body += ("\t"*level) + "if ("+var+".at("+str(level)+") == '"+key+"') {\n"
            body += value.to_cpp_code(var, level+1)
            body += ("\t"*level) + "}\n"
        return body

def generate_markov_dict(texts: List[str]) -> Dict[str, List[str]]:
    markov_dict = {}

    for text in texts:
        cleaned_punctuation = text.translate(str.maketrans('', '', string.punctuation))
        cleaned_punctuation = cleaned_punctuation.replace("’", "")
        words = ["", ""] + cleaned_punctuation.split(" ") + [""]
        for word1, word2, word3 in zip(words, words[1:], words[2:]):
            key = word1+" "+word2
            if key not in markov_dict:
                markov_dict[key] = []
            markov_dict[key].append(word3)
    return markov_dict

def get_text_from_dataset():
    n = 0
    max_n = 500
    out_data = []
    for row in dataset["train"].to_iterable_dataset():
        if n % 10 == 0:
            pass
            # print(n, len(out_data))
        text = row["answer"]
        out_data.append(text)
        n += 1
        if n == max_n:
            break
    return out_data

def main():
    ptn = PrefixTreeNode([])

    texts = get_text_from_dataset()
    # print(texts)

    words = generate_markov_dict(texts)
    # print(words["the"])

    for word1, payload in words.items():
        processed_payload = [unidecode(w.lower()) for w in payload] if len(word1) == 0 else [" "+unidecode(w.lower()) if len(w)>0 else "" for w in payload]
        ptn.add_child(unidecode(word1).lower()[::-1], processed_payload)
    # print(ptn.children['e'].children['h'].children['t'])
    print("bn::string<20> build_generated_message(bn::string<60> user_response, bn::string<60> last_word, bn::random rand) {")
    print(ptn.to_cpp_code("last_word", level=0))
    print("\treturn \"\";")
    print("}")




if __name__=="__main__":
    main()


