// git push -u origin main

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <filesystem>

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

Q_INVOKABLE QString Backend::checkFile(const QString &inputText) {
    std::ifstream f("./tmp_save.txt");

    if (f.good()) { // exists
        QString qtokens;
        QTextStream stream(&qtokens);
        std::string strInput{};

        while (std::getline(f, strInput))
            stream << QString::fromStdString(strInput) << '\n';
        return qtokens;
    } else {
        std::ofstream outf{ "tmp_save.txt", std::ios::out };

        if (!outf) {
            std::cerr << "Uh oh, Sample.txt could not be opened for writing!\n";
        }

        outf << inputText.toStdString();
        return inputText;
    }
    f.close();
}

Q_INVOKABLE QString Backend::deleteFile(const QString &inputText) {
    std::ifstream f{ "./tmp_save.txt" };

    if (f.good()) {
        QString qtokens;
        QTextStream stream(&qtokens);
        std::string strInput{};

        while (std::getline(f, strInput))
            stream << QString::fromStdString(strInput) << '\n';

        std::filesystem::remove("./tmp_save.txt");
        return qtokens;
    } else {
        return inputText;
    }
}
