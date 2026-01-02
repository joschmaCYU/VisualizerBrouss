#pragma once

#include <vector>
#include "compiler.hpp"

#include <brouss/src/include/tokenization.hpp>

[[nodiscard]] inline std::string to_string2(TokenType type) {
    switch (type) {
    case TokenType::exit: return "exit";
    case TokenType::return_: return "return";
    case TokenType::print: return "print";
    case TokenType::semi: return "semi";
    case TokenType::open_paren: return "open_paren";
    case TokenType::close_paren: return "close_paren";
    case TokenType::ident: return "ident";
    case TokenType::eq: return "eq";
    case TokenType::int_lit: return "int_lit";
    case TokenType::int_type: return "int_type";
    case TokenType::bool_true_lit: return "bool_true_lit";
    case TokenType::bool_false_lit: return "bool_false_lit";
    case TokenType::bool_type: return "bool_type";
    case TokenType::dot: return "dot";
    case TokenType::float_lit: return "float_lit";
    case TokenType::float_type: return "float_type";
    case TokenType::quote_s: return "quote_s"; // Single quote
    case TokenType::char_type: return "char_type";
    case TokenType::quote_d: return "quote_d"; // Double quote
    case TokenType::string_type: return "string_type";
    case TokenType::string_lit: return "string_lit";
    case TokenType::list_type: return "list_type";
    case TokenType::close_curly: return "close_curly";
    case TokenType::open_curly: return "open_curly";
    case TokenType::if_: return "if";
    case TokenType::while_: return "while";
    case TokenType::plus: return "plus";
    case TokenType::minus: return "minus";
    case TokenType::star: return "star";
    case TokenType::slash: return "slash";
    case TokenType::elif: return "elif";
    case TokenType::else_: return "else";
    default: return "unknown";
    }
}

struct Tree {
    Token tok;

    std::vector<Tree> children;

    Tree(Token iTok, std::vector<Tree> iChildren) {
        tok = iTok;
        children = iChildren;
    }

    bool operator==(const Tree& other) const {
        if (this->tok != other.tok) return false;
        if (this->children.size() != other.children.size()) return false;
        // Compare every child recursively
        for (size_t i = 0; i < children.size(); ++i) {
            if (!(this->children[i] == other.children[i])) {
                return false;
            }
        }
        return true;
    }

    // Add a 'depth' parameter with a default value of 0
    QString print_tree(int depth = 0) const {
        QString result;
        QTextStream stream(&result);

        // 1. Indentation
        for (int i = 0; i < depth; ++i) stream << "  ";
        if (depth > 0) stream << "|- ";

        if (tok.value.has_value()) {
            stream << QString::fromStdString(tok.value.value()) << ": " << QString::fromStdString(to_string2(tok.type)) << "\n";
        } else {
            stream << QString::fromStdString(to_string2(tok.type)) << "\n";
        }

        // 3. Recursion
        for (const Tree& child : children) {
            // Append the result of the children
            stream << child.print_tree(depth + 1);
        }

        return result;
    }

    Tree* find(const Tree& find_tree) {
        if (*this == find_tree) {
            return this;
        }

        for (Tree& child : children) {
            Tree* result = child.find(find_tree);
            if (result != nullptr) {
                return result;
            }
        }

        return {};
    }
};
