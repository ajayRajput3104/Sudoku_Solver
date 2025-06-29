#include "crow/app.h"
#include "sudoku_solver.cpp"

struct CORSHandler {
    struct context {};

    void before_handle(crow::request& req, crow::response& res, context&) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");

        // Handle CORS preflight OPTIONS request
        if (req.method == crow::HTTPMethod::OPTIONS) {
            res.code = 204;  // No content
            res.end();
        }
    }

    void after_handle(crow::request&, crow::response& res, context&) {
        // Add CORS headers to all responses
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    }
};

int main() {
    crow::App<CORSHandler> app;

    CROW_ROUTE(app, "/solve").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {
        crow::response res;

        auto body = crow::json::load(req.body);
        if (!body) {
            res.code = 400;
            res.body = "Invalid JSON format.";
            return res;
        }

        std::vector<std::vector<char>> board(9, std::vector<char>(9, '.'));

        try {
            for (int i = 0; i < 9; ++i)
                for (int j = 0; j < 9; ++j) {
                    std::string val = body[i][j].s();
                    board[i][j] = (val.empty() || val == "." || val == "0") ? '.' : val[0];
                }
        } catch (...) {
            res.code = 400;
            res.body = "Invalid board structure.";
            return res;
        }

        SudokuSolver solver;
        if (!solver.solveSudoku(board)) {
            res.code = 400;
            res.body = "Unsolvable puzzle.";
            return res;
        }

        crow::json::wvalue result;
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                result[i][j] = std::string(1, board[i][j]);

        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(result.dump());
        return res;
    });

    std::cout << "Sudoku Solver backend running at http://localhost:18080" << std::endl;
    app.port(18080).multithreaded().run();
}
