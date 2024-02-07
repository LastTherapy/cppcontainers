#include "../lib/s21_list.h"
#include <gtest/gtest.h>
using namespace s21;
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
  EXPECT_EQ(1, *my_list.begin()); // Проверяем, что первый элемент теперь 1
  EXPECT_EQ(
      1,
      *it); // Проверяем, что возвращаемый итератор указывает на новый элемент
}

// Тест на вставку в конец списка
TEST(ListTest, InsertAtEnd) {
  list<int> my_list{1, 2, 3};
  auto it = my_list.insert(my_list.end(), 4); // Вставляем 4 в конец списка
  // EXPECT_EQ(4, *--my_list.end());  // Проверяем, что последний элемент теперь
  // 4
  EXPECT_EQ(
      4,
      *it); // Проверяем, что возвращаемый итератор указывает на новый элемент
}

// Тест на вставку в середину списка
TEST(ListTest, InsertInMiddle) {
  list<int> my_list{1, 3, 4};
  auto it = my_list.begin();
  ++it; // Указываем на элемент со значением 3
  it = my_list.insert(it, 2); // Вставляем 2 перед 3

  // Проверяем, что вставка прошла успешно
  EXPECT_EQ(2, *it); // Вставленный элемент должен быть 2
  ++it;
  EXPECT_EQ(3, *it); // Следующий элемент должен быть 3
}

// Тест на вставку в пустой список
TEST(ListTest, InsertInEmptyList) {
  list<int> my_list;
  auto it = my_list.insert(my_list.begin(), 1); // Вставляем 1 в пустой список
  EXPECT_EQ(
      1,
      *my_list.begin()); // Проверяем, что список теперь содержит один элемент
  EXPECT_EQ(1, *it); // Возвращаемый итератор должен указывать на новый элемент
  EXPECT_EQ(1, my_list.size()); // Размер списка должен быть 1
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
  ASSERT_EQ(*it,
            3); // Проверяем второй элемент (который теперь является последним).
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

TEST(ListTest, SpliceToBeginning) {
  list<int> myList = {1, 2, 3};
  list<int> otherList = {4, 5, 6};

  myList.splice(myList.begin(), otherList);

  ASSERT_EQ(myList.size(), 6);
  ASSERT_TRUE(otherList.empty());
  ASSERT_EQ(myList.front(), 4); // Проверяем, что первый элемент - из otherList.

  // Проверяем порядок элементов.
  auto it = myList.begin();
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(*it++, 6);
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it, 3);
}

// Тестирование Splice в середину списка
TEST(ListTest, SpliceToMiddle) {
  list<int> myList = {1, 2, 3};
  list<int> otherList = {4, 5, 6};

  auto it = myList.begin();
  ++it;
  ++it; // Перемещаем итератор на позицию перед 3
  myList.splice(it, otherList);

  ASSERT_EQ(myList.size(), 6);
  ASSERT_TRUE(otherList.empty());
  it = myList.begin();
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(*it++, 6);
  ASSERT_EQ(*it, 3);
}

// Тестирование Splice в конец списка
TEST(ListTest, SpliceToEnd) {
  list<int> myList = {1, 2, 3};
  list<int> otherList = {4, 5, 6};

  myList.splice(myList.end(), otherList);

  ASSERT_EQ(myList.size(), 6);
  ASSERT_TRUE(otherList.empty());
  auto it = myList.begin();
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it++, 3);
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(*it, 6);
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
TEST(ListUniqueTest, UniqueFunctionality) {
  // Тестирование Удаления Последовательных Дубликатов
  {
    list<int> myList = {1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5, 6};
    myList.unique();
    std::vector<int> expected = {1, 2, 3, 4, 5, 6};
    int i = 0;
    for (auto elem : myList) {
      ASSERT_EQ(expected[i++], elem);
    }
  }

  // Тестирование С Пустым Списком
  {
    list<int> myList;
    myList.unique();
    ASSERT_TRUE(myList.empty());
  }

  // Тестирование С Списком Без Дубликатов
  {
    list<int> myList = {1, 2, 3, 4, 5};
    myList.unique();
    std::vector<int> expected = {1, 2, 3, 4, 5};
    int i = 0;
    for (auto elem : myList) {
      ASSERT_EQ(expected[i++], elem);
    }
  }

  // Тестирование С Всеми Дубликатами
  {
    list<int> myList = {2, 2, 2, 2, 2};
    myList.unique();
    std::vector<int> expected = {2};
    int i = 0;
    for (auto elem : myList) {
      ASSERT_EQ(expected[i++], elem);
    }
  }
}

TEST(ListSortTest, SortsList) {
  list<int> myList = {5, 3, 1, 4, 2};
  myList.sort();

  std::vector<int> expected = {1, 2, 3, 4, 5};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(expected[i++], elem);
  }
}

TEST(ListSortTest, HandlesEmptyList) {
  list<int> myList;
  myList.sort();

  ASSERT_TRUE(myList.empty());
}

TEST(ListSortTest, SingleElementList) {
  list<int> myList = {1};
  myList.sort();

  EXPECT_EQ(1, myList.front());
  EXPECT_EQ(1, myList.back());
}

TEST(ListSortTest, ListWithDuplicates) {
  list<int> myList = {3, 1, 4, 3, 2};
  myList.sort();

  std::vector<int> expected = {1, 2, 3, 3, 4};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(expected[i++], elem);
  }
}

TEST(ListConstructorTest, ParameterizedConstructor) {
  size_t n = 5;
  list<int> myList(n);

  ASSERT_EQ(myList.size(), n); // Проверяем размер списка

  for (auto &item : myList) {
    EXPECT_EQ(item, int()); // Проверяем, что все элементы инициализированы
                            // значением по умолчанию
  }
}

TEST(ListConstructorTest, InitializerListConstructor) {
  list<int> myList = {1, 2, 3, 4, 5};

  ASSERT_EQ(myList.size(), 5); // Проверяем размер списка

  std::vector<int> expected = {1, 2, 3, 4, 5};
  int i = 0;
  for (const auto &item : myList) {
    EXPECT_EQ(item, expected[i++]); // Проверяем каждый элемент списка
  }
}

TEST(ListConstructorTest, CopyConstructor) {
  list<int> originalList = {1, 2, 3, 4, 5};
  list<int> copiedList(originalList); // Использование конструктора копирования
  // Проверяем размер скопированного списка
  ASSERT_EQ(copiedList.size(), originalList.size());

  // Проверяем, что элементы скопированного списка совпадают с элементами
  // исходного
  auto origIt = originalList.begin();
  auto copyIt = copiedList.begin();
  while (origIt != originalList.end() && copyIt != copiedList.end()) {
    EXPECT_EQ(*origIt, *copyIt);
    ++origIt;
    ++copyIt;
  }
  // Изменяем исходный список и проверяем, что скопированный список не изменился
  originalList.push_front(0);
  ASSERT_NE(copiedList.size(), originalList.size());
}

// Тест на корректное копирование элементов списка.
TEST(ListCopy, CopyElements) {
  list<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  list<int> copy = original; // Использование оператора копирования.

  // Проверяем, что элементы скопировались корректно.
  ASSERT_EQ(copy.size(), original.size());
  auto copyIt = copy.begin();
  for (auto it = original.begin(); it != original.end(); ++it, ++copyIt) {
    EXPECT_EQ(*it, *copyIt);
  }
}

// Тест на независимость копии от оригинала.
TEST(ListCopy, IndependenceOfCopy) {
  list<int> original;
  original.push_back(1);
  original.push_back(2);

  list<int> copy = original;
  copy.push_back(3); // Изменяем копию.

  // Проверяем, что изменения в копии не затронули оригинал.
  ASSERT_EQ(original.size(), 2);
  ASSERT_EQ(copy.size(), 3);
}

// Тест на копирование пустого списка.
TEST(listCopy, CopyEmptylist) {
  list<int> original;
  list<int> copy = original;

  // Проверяем, что копия пустого списка также пуста.
  ASSERT_TRUE(copy.empty());
}

// Тест на перемещение содержимого одного списка в другой.
TEST(ListMoveAssignment, MoveElements) {
  list<int> source;
  source.push_back(1);
  source.push_back(2);
  source.push_back(3);

  list<int> destination;
  destination =
      std::move(source); // Использование оператора присваивания перемещением.

  // Проверяем, что source теперь пустой.
  ASSERT_TRUE(source.empty());

  // Проверяем, что элементы были перемещены в destination.
  ASSERT_EQ(destination.size(), 3);
  auto it = destination.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

// Тест на самоприсваивание при присваивании перемещением.
TEST(ListMoveAssignment, SelfAssignment) {
  list<int> myList;
  myList.push_back(1);
  myList.push_back(2);

  myList = std::move(myList); // Самоприсваивание перемещением.

  // Проверяем, что список не изменился.
  ASSERT_EQ(myList.size(), 2);
  auto it = myList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

// Тест на присваивание перемещением в пустой список.
TEST(ListMoveAssignment, MoveToEmptyList) {
  list<int> source;
  source.push_back(1);
  source.push_back(2);

  list<int> destination;

  destination = std::move(source); // Перемещение в пустой список.

  // Проверяем, что source теперь пустой.
  ASSERT_TRUE(source.empty());

  // Проверяем, что элементы были перемещены в destination.
  ASSERT_EQ(destination.size(), 2);
  auto it = destination.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(ListInsertManyBack, AddToEmptyList) {
  list<int> list;
  list.insert_many_back(1, 2, 3);

  // Проверяем размер и элементы списка.
  ASSERT_EQ(list.size(), 3);
  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

// Тест на добавление нескольких элементов в конец непустого списка.
TEST(ListInsertManyBack, AddToNonEmptyList) {
  list<int> list;
  list.push_back(0); // Добавляем начальный элемент.
  list.insert_many_back(1, 2, 3);

  // Проверяем размер и элементы списка.
  ASSERT_EQ(list.size(), 4);
  auto it = list.begin();
  EXPECT_EQ(*it, 0);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

// Тест на добавление одного элемента (проверка variadic аргументов).
TEST(ListInsertManyBack, AddSingleElement) {
  list<int> list;
  list.insert_many_back(1);

  // Проверяем размер и элементы списка.
  ASSERT_EQ(list.size(), 1);
  auto it = list.begin();
  EXPECT_EQ(*it, 1);
}

TEST(ListInsertManyBack, AddDifferentTypes) {
  list<std::variant<int, std::string>> list;
  list.insert_many_back(1, "two", 3);

  // Проверяем размер и элементы списка.
  ASSERT_EQ(list.size(), 3);
  auto it = list.begin();
  EXPECT_EQ(std::get<int>(*it), 1);
  ++it;
  EXPECT_EQ(std::get<std::string>(*it), "two");
  ++it;
  EXPECT_EQ(std::get<int>(*it), 3);
}

TEST(ListInsertManyFront, AddToEmptyList) {
  list<int> list;
  list.insert_many_front(1, 2, 3);

  // Проверяем размер и элементы списка.
  ASSERT_EQ(list.size(), 3);
  auto it = list.begin();
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 1);
}

// Тест на добавление нескольких элементов в начало непустого списка.
TEST(ListInsertManyFront, AddToNonEmptyList) {
  list<int> list;
  list.push_back(0); // Добавляем начальный элемент.
  list.insert_many_front(1, 2, 3);

  // Проверяем размер и элементы списка.
  ASSERT_EQ(list.size(), 4);
  auto it = list.begin();
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 0);
}

// Тест на добавление одного элемента (проверка variadic аргументов).
TEST(ListInsertManyFront, AddSingleElement) {
  list<int> list;
  list.insert_many_front(1);

  // Проверяем размер и элементы списка.
  ASSERT_EQ(list.size(), 1);
  auto it = list.begin();
  EXPECT_EQ(*it, 1);
}

// Тест на проверку порядка вставки элементов.
TEST(ListInsertManyFront, CheckOrder) {
  list<int> list;
  list.insert_many_front(1, 2, 3, 4);

  // Проверяем размер и элементы списка.
  ASSERT_EQ(list.size(), 4);
  auto it = list.begin();
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 1);
}

// Тест на добавление нескольких элементов в начало непустого списка.
TEST(ListInsertManyFront2, AddToNonEmptyList) {
  list<int> mylist;
  mylist.insert_many_front(0); // Добавляем начальный элемент.
  mylist.insert_many_front(1, 2, 3);

  // Проверяем размер и элементы списка.
  ASSERT_EQ(mylist.size(), 4);
  auto it = mylist.begin();
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 0);
}

TEST(ListInsertMany, InsertIntoEmptyList) {
  list<int> mylist;
  auto pos = mylist.begin();
  auto ret = mylist.insert_many(pos, 1, 2, 3);

  ASSERT_EQ(mylist.size(), 3);
  EXPECT_EQ(*ret, 1); // Проверяем возвращаемое значение
  auto it = mylist.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(ListInsertMany, InsertIntoMiddle) {
  list<int> mylist{1, 4, 5};
  auto pos = mylist.begin();
  ++pos; // Перемещаем на одну позицию вперед
  auto ret = mylist.insert_many(pos, 2, 3);

  ASSERT_EQ(mylist.size(), 5);
  EXPECT_EQ(*ret, 2); // Проверяем возвращаемое значение
  auto it = mylist.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(ListInsertMany, InsertAtEnd) {
  list<int> mylist{1, 2};
  auto ret = mylist.insert_many(mylist.end(), 3, 4);

  ASSERT_EQ(mylist.size(), 4);
  EXPECT_EQ(*ret, 3); // Проверяем возвращаемое значение
  auto it = mylist.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(ListInsertMany, InsertSingleElement) {
  list<int> mylist{1, 2, 4};
  auto pos = mylist.begin();
  ++pos;
  ++pos; // Перемещаем на две позиции вперед
  auto ret = mylist.insert_many(pos, 3);

  ASSERT_EQ(mylist.size(), 4);
  EXPECT_EQ(*ret, 3); // Проверяем возвращаемое значение
  auto it = mylist.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}