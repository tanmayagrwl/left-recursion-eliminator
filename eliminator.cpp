#include <iostream>
#include <vector>
#include <string>
using namespace std;

class NonTerminal {
    string name;                    // Stores the head of the production rule
    vector<string> productionRules; // Stores the body of production rules

public:
    NonTerminal(string name) {
        this->name = name;
    }

    // Returns the head of the production rule
    string getName() {
        return name;
    }

    // Sets the production rules
    void setRules(vector<string> rules) {
        productionRules.clear();
        for (auto rule : rules) {
            productionRules.push_back(rule);
        }
    }

    // Returns the production rules
    vector<string> getRules() {
        return productionRules;
    }

    // Adds a single production rule
    void addRule(string rule) {
        productionRules.push_back(rule);
    }

    // Prints the production rules
    void printRule() {
        string toPrint = "";
        toPrint += name + " ->";
        for (string s : productionRules) {
            toPrint += " " + s + " |";
        }
        if (!productionRules.empty())
            toPrint.pop_back(); // remove last '|'
        cout << toPrint << endl;
    }
};

class Grammar {
    vector<NonTerminal> nonTerminals;

public:
    // Reads rules from user input
    void inputData() {
        int n;
        cout << "Enter the number of production rules: ";
        cin >> n;
        cin.ignore();  // ignore newline after integer input
        
        cout << "Enter the production rules in the format: A -> production1 | production2 | ...\n";
        for (int i = 0; i < n; i++) {
            string rule;
            getline(cin, rule);
            addRule(rule);
        }
    }

    // Adds a rule to the grammar
    void addRule(string rule) {
        size_t arrowPos = rule.find("->"); // Find the position of "->"
        if (arrowPos == string::npos) {
            cout << "Invalid rule format: " << rule << endl;
            return;
        }
    
        // Extract the nonterminal (left-hand side)
        string nonTerminal = rule.substr(0, arrowPos);
        nonTerminal.erase(remove(nonTerminal.begin(), nonTerminal.end(), ' '), nonTerminal.end()); // Remove spaces
    
        // Extract the production rules (right-hand side)
        string productions = rule.substr(arrowPos + 2);
        productions.erase(remove(productions.begin(), productions.end(), ' '), productions.end()); // Remove spaces
    
        // Split the productions by '|'
        vector<string> rules;
        size_t start = 0;
        size_t end = productions.find('|');
        while (end != string::npos) {
            rules.push_back(productions.substr(start, end - start));
            start = end + 1;
            end = productions.find('|', start);
        }
        rules.push_back(productions.substr(start)); // Add the last rule
    
        // Add the nonterminal and its rules to the grammar
        bool ntFound = false;
        for (auto &nt : nonTerminals) {
            if (nt.getName() == nonTerminal) {
                ntFound = true;
                for (auto &rule : rules) {
                    nt.addRule(rule);
                }
                break;
            }
        }
        if (!ntFound) {
            NonTerminal newNT(nonTerminal);
            for (auto &rule : rules) {
                newNT.addRule(rule);
            }
            nonTerminals.push_back(newNT);
        }
    }
    // Eliminates indirect left recursion: For a given nonterminal A and a previous nonterminal B
    void solveNonImmediateLR(NonTerminal &A, NonTerminal &B) {
        string nameA = A.getName();
        string nameB = B.getName();

        vector<string> rulesA = A.getRules();
        vector<string> rulesB = B.getRules();
        vector<string> newRulesA;

        for (auto rule : rulesA) {
            // If the rule begins with B, replace B with its productions
            if (rule.substr(0, nameB.size()) == nameB) {
                for (auto rule1 : rulesB) {
                    newRulesA.push_back(rule1 + rule.substr(nameB.size()));
                }
            } else {
                newRulesA.push_back(rule);
            }
        }
        A.setRules(newRulesA);
    }

    // Eliminates immediate left recursion for nonterminal A
    void solveImmediateLR(NonTerminal &A) {
        string name = A.getName();
        string newName = name + "'";

        vector<string> alphas, betas;
        vector<string> rules = A.getRules();
        vector<string> newRulesA, newRulesA1;

        // Separate the productions into those with immediate left recursion (alphas)
        // and those without (betas)
        for (auto rule : rules) {
            if (rule.substr(0, name.size()) == name) {
                // Remove the left recursion portion
                alphas.push_back(rule.substr(name.size()));
            } else {
                betas.push_back(rule);
            }
        }

        // If no immediate left recursion exists, then nothing to do
        if (alphas.empty())
            return;

        // If there are no betas, then we must allow for the possibility of an empty production
        if (betas.empty())
            newRulesA.push_back(newName);

        // Rewrite productions for A: A -> betaA'
        for (auto beta : betas)
            newRulesA.push_back(beta + newName);

        // Rewrite productions for the new nonterminal A': A' -> alphaA' | ε
        for (auto alpha : alphas)
            newRulesA1.push_back(alpha + newName);

        // Amend the original rule for A
        A.setRules(newRulesA);

        // Add ε (epsilon) to indicate an empty production
        newRulesA1.push_back("\u03B5"); // using Greek letter epsilon

        // Create new nonterminal A' and add it to the grammar
        NonTerminal newNonTerminal(newName);
        newNonTerminal.setRules(newRulesA1);
        nonTerminals.push_back(newNonTerminal);
    }

    // Eliminates both indirect and immediate left recursion for the entire grammar
    void applyAlgorithm() {
        int size = nonTerminals.size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < i; j++) {
                solveNonImmediateLR(nonTerminals[i], nonTerminals[j]);
            }
            solveImmediateLR(nonTerminals[i]);
        }
    }

    // Prints all production rules of the grammar
    void printRules() {
        for (auto nonTerminal : nonTerminals) {
            nonTerminal.printRule();
        }
    }
};

int main(){
    Grammar grammar;
    grammar.inputData();
    grammar.applyAlgorithm();
    cout << "\nGrammar after eliminating left recursion:\n";
    grammar.printRules();

    return 0;
}
