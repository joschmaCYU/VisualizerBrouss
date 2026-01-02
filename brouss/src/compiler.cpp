// git push -u origin main

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "compiler.hpp"

#include "../src/include/tokenization.hpp"
#include "../src/include/generation.hpp"
#include "../src/include/parser.hpp"


// git push -u origin main

std::vector<Token> gen_token(std::string contents) {
    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();
    tokens.push_back({.type = TokenType::semi });
    return tokens;
}

QString Backend::tokens_str(const QString &inputText) {
    std::string contents = inputText.toStdString();
    std::vector<Token> tokens = gen_token(contents);
    QString qtokens;
    QTextStream stream(&qtokens);

    for (Token token : tokens) {
        if (token.value.has_value()) {
            stream << QString::fromStdString(token.value.value()) << ":" << QString::fromStdString(to_string(token.type)) << " ";
        } else {
            stream << QString::fromStdString(to_string(token.type)) << " ";
        }

        if (token.type == TokenType::semi) {
            stream << "\n";
        }
    }
    return qtokens;
}

std::optional<NodeProg> gen_parse(Parser& parser) {
    std::optional<NodeProg> prog = parser.parse_prog();

    if (!prog.has_value()) {
        std::cerr << "Invalid program" << std::endl;
        exit(EXIT_FAILURE);
    }

    return prog;
}


Q_INVOKABLE QString Backend::parse_str(const QString &inputText) {
    std::string contents = inputText.toStdString();
    std::vector<Token> tokens = gen_token(contents);

    Parser parser(std::move(tokens));
    std::optional<NodeProg> prog = gen_parse(parser);

    return parser.tree.print_tree();
}

std::string gen_asm(const std::optional<NodeProg> prog) {
    Generator generator(prog.value());
    return generator.gen_prog();
}

Q_INVOKABLE QString Backend::assemble_str(const QString &inputText) {
    std::string contents = inputText.toStdString();
    std::vector<Token> tokens = gen_token(contents);

    Parser parser(std::move(tokens));
    std::optional<NodeProg> prog = gen_parse(parser);
    return QString::fromStdString(gen_asm(prog));
}


// ./brouss ; ./out ; echo $?
int Backend::launch(const QString &inputText) {
    std::string contents = inputText.toStdString();
    //std::cout << contents << std::endl;

    std::vector<Token> tokens = gen_token(contents);
    //std::cout << tokens.size() << std::endl;
    //for (Token token : tokens) {
    //std::cout << to_string(token.type) << std::endl;
    //}

    Parser parser(std::move(tokens));
    std::optional<NodeProg> prog = gen_parse(parser);
    Generator generator(prog.value());
    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.gen_prog();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return 0;
}
