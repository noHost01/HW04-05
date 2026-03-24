#include <iostream>
#include <vector>
#include <string>
#include <map>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe 
{
    public:
        std::string potionName;
        std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

        // 생성자: 재료 목록을 받아 초기화하도록 수정
        PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
            : potionName(name), ingredients(ingredients) {}

        // 정보를 화면에 출력하는 함수
        void print() const
        {
            std::cout << "- Name of Potion : " << potionName << std::endl;
            std::cout << "  > Required Materials : ";

            for (size_t i = 0; i < ingredients.size(); ++i)
            {
                std::cout << ingredients[i];
                if (i < ingredients.size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop 
{
    private:
        std::vector<PotionRecipe> recipes;

    public:
        // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
        void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) 
        {
            recipes.push_back(PotionRecipe(name, ingredients));
            std::cout << ">> a new recipe '" << name << "'Added." << std::endl;
        }

        // 모든 레시피 출력 메서드
        void displayAllRecipes() const 
        {
            if (recipes.empty()) 
            {
                std::cout << "There is no registered recipe yet." << std::endl;
                return;
            }

            std::cout << "\n--- [Full recipe list] ---" << std::endl;
            for (size_t i = 0; i < recipes.size(); ++i) 
            {
                std::cout << "- Name of potion : " << recipes[i].potionName << std::endl;
                std::cout << "  > Required Materials : ";

                // 재료 목록을 순회하며 출력
                for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) 
                {
                    std::cout << recipes[i].ingredients[j];
                    // 마지막 재료가 아니면 쉼표로 구분
                    if (j < recipes[i].ingredients.size() - 1) 
                    {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << "---------------------------\n";
        }

        // 물약이름 기반으로 레시피를 찾아서, 해당 레시피 객체의 주소를 반환하는 함수
        PotionRecipe* searchRecipeByName(const std::string& name)
        {
            for (size_t i = 0; i < recipes.size(); ++i)
            {
                if (recipes[i].potionName == name)
                {
                    return &recipes[i];
                }
            }
            return nullptr;
        }

        // 재료이름 기반으로 레시피를 찾아서, 해당 재료를 포함한 레시피 객체들을 vector로 반환하는 함수
        std::vector<PotionRecipe> searchRecipeByIngredient(const std::string& ingredient)
        {
            std::vector<PotionRecipe> result;

            for (size_t i = 0; i < recipes.size(); ++i)
            {
                for (size_t j = 0; j < recipes[i].ingredients.size(); ++j)
                {
                    if (recipes[i].ingredients[j] == ingredient)
                    {
                        result.push_back(recipes[i]);
                        break; // 중복 방지..
                    }
                }
            }
            return result;
        }
};

// 포션 생성시 3개 지급 재고에 따른 추가 감소
class StockManager
{
    private:
        std::map<std::string, int> potionStock;
        const int MAX_STOCK = 3;

    public:
        void initializeStock(const std::string& potionName)
        {
            potionStock[potionName] = MAX_STOCK;
        }

        bool dispensePotion(const std::string& potionName)
        {
            // 재고가 존재하고 1 이상인지 확인
            if (potionStock[potionName] > 0)
            {
                potionStock[potionName]--;

                return true;
            }
            return false;
        }

        bool returnPotion(const std::string& potionName)
        {
            if (potionStock[potionName] < MAX_STOCK)
            {
                potionStock[potionName]++;
                return true;
            }
            return false;
        }
};

int main() 
{
    AlchemyWorkshop myWorkshop;
    StockManager stockManager;

    while (true) 
    {
        std::cout << "* Alchemy Workshop Management System" << std::endl;
        std::cout << "1. Add a Recipe" << std::endl;
        std::cout << "2. Output All Recipes" << std::endl;
        std::cout << "3. Give potion (search)" << std::endl;
        std::cout << "4. Return potion" << std::endl;
        std::cout << "5. Ends" << std::endl;
        std::cout << "Choice : ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) 
        {
            std::cout << "Invalid input, please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) 
        {
            std::string name;
            std::cout << "Name of potion : ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "Enter the necessary materials. (Enter 'End' when you complete the input)" << std::endl;

            while (true) 
            {
                std::cout << "Enter Material : ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "End") 
                {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) 
            {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else 
            {
                std::cout << ">> The ingredients are not entered, cancel the Add recipe." << std::endl;
            }

        }
        else if (choice == 2) 
        {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3)
        {
            std::string input;
            std::cout << "Enter potion name or ingredient : ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, input);

            // 1. 이름으로 먼저 검색
            PotionRecipe* recipe = myWorkshop.searchRecipeByName(input);

            if (recipe != nullptr)
            {
                if (stockManager.dispensePotion(recipe->potionName))
                {
                    std::cout << "Potion given!" << std::endl;
                }
                else
                {
                    std::cout << "Out of Stock!" << std::endl;
                }
            }
            else
            {
                // 2. 재료로 검색
                std::vector<PotionRecipe> results = myWorkshop.searchRecipeByIngredient(input);

                if (results.empty())
                {
                    std::cout << "No matching recipes found." << std::endl;
                }
                else
                {
                    for (auto& r : results)
                    {
                        if (stockManager.dispensePotion(r.potionName))
                        {
                            std::cout << r.potionName << " given!" << std::endl;
                        }
                        else
                        {
                            std::cout << r.potionName << " is out of stock!" << std::endl;
                        }
                    }
                }
            }
        }
        else if (choice == 4)
        {
            std::string name;
            std::cout << "Enter potion name to return : ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            if (stockManager.returnPotion(name))
            {
                std::cout << "Potion returned!" << std::endl;
            }
            else
            {
                std::cout << "Stock is already full!" << std::endl;
            }
        }
        else if (choice == 5) 
        {
            std::cout << "I'm closing the workshop..." << std::endl;
            break;
        }
        else 
        {
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    }
    return 0;
}