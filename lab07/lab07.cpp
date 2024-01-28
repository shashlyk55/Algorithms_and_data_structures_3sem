#include <iostream>
#include <vector>

/*
1.	Разработать приложение, которые будет находить возрастающую подпоследовательность.
2.	Пользователь вводит N – число элементов последовательности.
3.	Приложении находит длину максимальной подпоследовательности и выводит пользователю на экран. На новой строке выводит максимальную (одну из максимальных) возрастающую подпоследовательность.

Например, имеется последовательность - 5, 10, 6, 12, 3, 24, 7, 8
Ответ:
4
5, 6, 7, 8

*/


// Функция для нахождения максимальной возрастающей подпоследовательности
std::vector<int> findMaxIncreasingSubsequence(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> dp(n, 1); // Инициализируем массив dp значениями 1

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    int max_length = 0;
    int max_index = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > max_length) {
            max_length = dp[i];
            max_index = i;
        }
    }

    // Создаем максимальную возрастающую подпоследовательность
    std::vector<int> result;
    int current_length = max_length;
    for (int i = max_index; i >= 0; i--) {
        if (dp[i] == current_length) {
            result.insert(result.begin(), nums[i]);
            current_length--;
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "ru");
    std::vector<int> nums = { 1, 3, 5, 4, 7, 8, 9, 2 };

    std::vector<int> maxSubsequence = findMaxIncreasingSubsequence(nums);

    std::cout << "Длина максимальной возрастающей подпоследовательности: " << maxSubsequence.size() << std::endl;

    std::cout << "Максимальная возрастающая подпоследовательность: ";
    for (int num : maxSubsequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
