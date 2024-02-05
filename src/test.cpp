#include <gtest/gtest.h>
#include "lib/list.h" 

// Тест на проверку создания пустого списка
TEST(ListTest, CreatesEmptyList) {
    list<int> my_list;
    EXPECT_TRUE(my_list.empty());
    EXPECT_EQ(0, my_list.size());
}

// Тест на добавление элементов в список
TEST(ListTest, CanAddItems) {
    list<int> my_list;
    my_list.push_back(1); // Предполагается, что у вас есть такой метод
    my_list.push_back(2);

    EXPECT_FALSE(my_list.empty());
    EXPECT_EQ(2, my_list.size());
}

// Тест на корректность итерации по списку
TEST(ListTest, CanIterateList) {
    list<int> my_list{1, 2, 3}; // Инициализация с помощью списка инициализации
    int sum = 0;
    for (auto it = my_list.begin(); it != my_list.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(6, sum); // 1+2+3 должно быть равно 6
}

// Тест на корректность front и back
TEST(ListTest, CorrectFrontAndBack) {
    list<int> my_list{1, 2, 3, 4};
    EXPECT_EQ(1, my_list.front());
    EXPECT_EQ(4, my_list.back());
}

TEST(ListTest, ClearsList) {
    list<int> my_list{1, 2, 3};
    my_list.clear();
    EXPECT_TRUE(my_list.empty());
}

// Тест на добавление элементов в произвольное место списка
TEST(ListTest, InsertsElements) {
    list<int> my_list{1, 3, 4};
    auto it = my_list.begin();
    ++it; // Указываем на элемент со значением 3
    my_list.insert(it, 2); // Вставляем 2 перед 3

    // Проверяем, что элементы расположены в правильном порядке
    int expected[] = {1, 2, 3, 4};
    int i = 0;
    for (auto elem : my_list) {
        EXPECT_EQ(expected[i++], elem);
    }
}

// Тест на вставку в начало списка
TEST(ListTest, InsertAtBegin) {
    list<int> my_list{2, 3, 4};
    auto it = my_list.insert(my_list.begin(), 1); // Вставляем 1 в начало списка
    EXPECT_EQ(1, *my_list.begin());  // Проверяем, что первый элемент теперь 1
    EXPECT_EQ(1, *it);  // Проверяем, что возвращаемый итератор указывает на новый элемент
}

// Тест на вставку в конец списка
TEST(ListTest, InsertAtEnd) {
    list<int> my_list{1, 2, 3};
    auto it = my_list.insert(my_list.end(), 4); // Вставляем 4 в конец списка
    // EXPECT_EQ(4, *--my_list.end());  // Проверяем, что последний элемент теперь 4
    EXPECT_EQ(4, *it);  // Проверяем, что возвращаемый итератор указывает на новый элемент
}

// Тест на вставку в середину списка
TEST(ListTest, InsertInMiddle) {
    list<int> my_list{1, 3, 4};
    auto it = my_list.begin();
    ++it; // Указываем на элемент со значением 3
    it = my_list.insert(it, 2); // Вставляем 2 перед 3

    // Проверяем, что вставка прошла успешно
    EXPECT_EQ(2, *it);  // Вставленный элемент должен быть 2
    ++it;
    EXPECT_EQ(3, *it);  // Следующий элемент должен быть 3
}

// Тест на вставку с использованием range-based for loop
// TEST(ListTest, InsertUsingRangeFor) {
//     list<int> my_list{1, 2, 4, 5};
//     auto it = my_list.begin();
//     std::advance(it, 2); // Перемещаем итератор на позицию перед которой будет вставка
//     it = my_list.insert(it, 3); // Вставляем 3 перед 4

//     int expected[] = {1, 2, 3, 4, 5};
//     int i = 0;
//     for (int val : my_list) {
//         EXPECT_EQ(expected[i++], val);
//     }
// }

// Тест на вставку в пустой список
TEST(ListTest, InsertInEmptyList) {
    list<int> my_list;
    auto it = my_list.insert(my_list.begin(), 1); // Вставляем 1 в пустой список
    EXPECT_EQ(1, *my_list.begin());  // Проверяем, что список теперь содержит один элемент
    EXPECT_EQ(1, *it);  // Возвращаемый итератор должен указывать на новый элемент
    EXPECT_EQ(1, my_list.size());  // Размер списка должен быть 1
}

// Тест на удаление элемента из списка
TEST(ListTest, ErasesElement) {
    list<int> my_list{1, 2, 3};
    auto it = my_list.begin();
    ++it; // Указываем на элемент со значением 2
    my_list.erase(it);

    // Проверяем, что элемент 2 был удален
    int expected[] = {1, 3};
    int i = 0;
    for (auto elem : my_list) {
        EXPECT_EQ(expected[i++], elem);
    }
}

TEST(ListTest, EraseBegin) {
    list<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);

    myList.erase(myList.begin());
    ASSERT_EQ(myList.size(), 2);
    ASSERT_EQ(*myList.begin(), 2);
}

// TEST(ListTest, EraseEnd) {
//     list<int> myList;
//     myList.push_back(1);
//     myList.push_back(2);
//     myList.push_back(3);

//     myList.erase(--myList.end());
//     ASSERT_EQ(myList.size(), 2);
//     ASSERT_NE(myList.end(), myList.find(3)); // Предполагая, что есть метод find
// }

TEST(ListTest, EraseMiddle) {
    list<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);

    auto it = myList.begin();
    ++it; // Это устанавливает итератор на второй элемент (со значением 2).
    myList.erase(it); // Удаляем второй элемент.

    // Теперь нужно получить новый итератор, так как 'it' больше не валиден.
    it = myList.begin();
    ASSERT_EQ(myList.size(), 2);
    ASSERT_EQ(*it, 1); // Проверяем первый элемент.
    ++it;
    ASSERT_EQ(*it, 3); // Проверяем второй элемент (который теперь является последним).
}


TEST(ListTest, EraseSingleElement) {
    list<int> myList;
    myList.push_back(1);

    myList.erase(myList.begin());
    ASSERT_TRUE(myList.empty());
}

TEST(ListTest, EraseEmptyList) {
    list<int> myList;
    myList.erase(myList.begin()); // Ничего не должно произойти.
    ASSERT_TRUE(myList.empty());
}

TEST(ListTest, EraseLastElement) {
    list<int> myList;
    myList.push_back(1);
    myList.push_back(2);

    myList.erase(--myList.end());
    ASSERT_EQ(myList.size(), 1);
    ASSERT_EQ(*myList.begin(), 1);
}

// Тест на добавление элемента в конец списка
TEST(ListTest, PushesBackElement) {
    list<int> my_list;
    my_list.push_back(1);
    EXPECT_EQ(1, my_list.back());
}

// Тест на добавление элемента в начало списка
TEST(ListTest, PushesFrontElement) {
    list<int> my_list;
    my_list.push_front(1);
    EXPECT_EQ(1, my_list.front());
}

// Тест на удаление элемента из конца списка
TEST(ListTest, PopsBackElement) {
    list<int> my_list{1, 2, 3, 4};
    my_list.pop_back();
    EXPECT_EQ(3, my_list.back());
}

// Тест на удаление элемента из начала списка
TEST(ListTest, PopsFrontElement) {
    list<int> my_list{1, 2, 3, 4};
    my_list.pop_front();
    EXPECT_EQ(2, my_list.front());
}

// Тест на обмен содержимым списков
TEST(ListTest, SwapsLists) {
    list<int> my_list1{1, 2, 3};
    list<int> my_list2{4, 5, 6};
    my_list1.swap(my_list2);

    EXPECT_EQ(4, my_list1.front());
    EXPECT_EQ(1, my_list2.front());
}

// Тест на слияние двух списков
TEST(ListTest, MergesLists) {
    list<int> my_list1{1, 3, 5};
    list<int> my_list2{2, 4, 6};
    my_list1.merge(my_list2);

    // Проверяем, что my_list2 теперь пустой
    EXPECT_TRUE(my_list2.empty());

    // Проверяем, что элементы в my_list1 теперь идут по порядку
    int expected[] = {1, 2, 3, 4, 5, 6};
    int i = 0;
    for (auto elem : my_list1) {
        EXPECT_EQ(expected[i++], elem);
    }
}

// Тест на переворот списка
TEST(ListTest, ReversesList) {
    list<int> my_list{1, 2, 3};
    my_list.reverse();

    int expected[] = {3, 2, 1};
    int i = 0;
    for (auto elem : my_list) {
        EXPECT_EQ(expected[i++], elem);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
