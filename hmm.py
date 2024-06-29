import random
from typing import List


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




def main():
    ptn = PrefixTreeNode([])

    words = {
        "": ["1", "2"],
        "1": ["x", "y"],
        "2": ["a", "b"]
    }

    for word1, payload in words.items():
        ptn.add_child(word1.lower(), [w.lower() for w in payload])

    print(ptn.to_cpp_code("computer_response_so_far"))





if __name__=="__main__":
    main()


