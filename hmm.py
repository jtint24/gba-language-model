import random
import string
from typing import List, Dict


class PrefixTreeNode:
    def __init__(self, payload: List[str]):
        self.children = {}
        self.payload = payload

    def add_child_single(self, char: str, payload: List[str]):
        self.children[char] = PrefixTreeNode(payload)

    def add_child(self, key: str, payload: List[str]):
        if len(key) == 0:
            self.payload += payload
        elif len(key) == 1:
            self.add_child_single(key, payload)
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
        words = [""] + cleaned_punctuation.split(" ") + [""]
        for word1, word2 in zip(words, words[1:]):
            if word1 not in markov_dict:
                markov_dict[word1] = []
            markov_dict[word1].append(word2)
    return markov_dict

def main():
    ptn = PrefixTreeNode([])

    texts = [
        "Hello",
        "Hi",
        "Hey",
        "Good morning",
        "Good afternoon",
        "Good evening",
        "How are you?",
        "How’s it going?",
        "What’s up?",
        "Howdy",
        "Greetings",
        "Nice to meet you",
        "How have you been?",
        "Long time no see",
        "What’s new?",
        "How’s everything?",
        "How’s your day going?",
        "It’s good to see you",
        "Welcome",
        "Hiya",
        "Hi, how’s your day going?",
        "Hello! What have you been up to lately?",
        "Hey, do you have any plans for the weekend?",
        "Good morning! How did you sleep?",
        "Hi there! What’s new with you?",
        "Hello! How’s work (or school) been?",
        "Hey, have you seen any good movies recently?",
        "Good afternoon! Have you tried any new restaurants lately?",
        "Hi! What’s your favorite way to spend a day off?",
        "Hello! Do you have any hobbies you’re passionate about?",
        "Hey, how’s your family doing?",
        "Good evening! What’s the best book you’ve read recently?",
        "Hi there! Do you follow any sports teams?",
        "Hello! What’s the most interesting thing you’ve learned recently?",
        "Hey, do you have any travel plans coming up?",
        "Good morning! What’s your favorite type of music?",
        "Hi! Do you like cooking? What’s your favorite dish to make?",
        "Hello! How do you like to unwind after a long day?",
        "Hey, have you been to any fun events lately?",
        "Good afternoon! What’s your favorite way to stay active?",
    ]

    words = generate_markov_dict(texts)

    for word1, payload in words.items():
        processed_payload = [w.lower() for w in payload] if len(word1) == 0 else [" "+w.lower() if len(w)>0 else "" for w in payload]
        ptn.add_child(word1.lower()[::-1], processed_payload)

    print(ptn.to_cpp_code("last_word"))





if __name__=="__main__":
    main()


