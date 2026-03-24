#include <iostream>
#include <vector>
#include <string>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> a new recipe '" << name << "'Added." << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "There is no registered recipe yet." << std::endl;
            return;
        }

        std::cout << "\n--- [Full recipe list] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- Name of potion : " << recipes[i].potionName << std::endl;
            std::cout << "  > Required Materials : ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }
};

int main() {
    AlchemyWorkshop myWorkshop;

    while (true) {
        std::cout << "* Alchemy Workshop Management System" << std::endl;
        std::cout << "1. Add a recipe" << std::endl;
        std::cout << "2. Output all recipes" << std::endl;
        std::cout << "3. Ends" << std::endl;
        std::cout << "Choice : ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input, please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "Name of potion : ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "Enter the necessary materials. (Enter 'End' when you complete the input)" << std::endl;

            while (true) {
                std::cout << "Enter Material : ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "End") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> The ingredients are not entered, cancel the Add recipe." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) {
            std::cout << "I'm closing the workshop..." << std::endl;
            break;

        }
        else {
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    }

    return 0;
}