#include <iostream>

// Структура для представлення елемента розрідженого списку
template <typename T>
struct Node {
    T data;        // Значення елемента
    int column;    // Номер стовпця, в якому знаходиться елемент
    Node* next;    // Вказівник на наступний елемент списку

    // Конструктор для створення нового елемента
    Node(T value, int col) : data(value), column(col), next(nullptr) {}
};

// Клас для реалізації розрідженого списку
template <typename T>
class SparseMatrix {
private:
    Node<T>* head;   // Вказівник на перший елемент списку

public:
    // Конструктор за замовчуванням для ініціалізації голови списку
    SparseMatrix() : head(nullptr) {}

    // Додавання елемента до списку
    void addElement(T value, int row, int col) {
        Node<T>* newNode = new Node<T>(value, col);
        if (!head || col < head->column) {
            // Додавання елемента на початок списку або перед першим елементом
            newNode->next = head;
            head = newNode;
        } else {
            // Додавання елемента в середину списку або в кінець
            Node<T>* current = head;
            while (current->next && current->next->column < col) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Доступ за індексом
    T getElement(int row, int col) {
        Node<T>* current = head;
        while (current && current->column < col) {
            current = current->next;
        }
        if (current && current->column == col) {
            return current->data;
        } else {
            return T(); // Повертаємо значення за замовчуванням, якщо елемент не знайдено
        }
    }

    // Пошук за значенням
    bool searchByValue(T value) {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Пошук першого елемента за заданою умовою
    Node<T>* searchByCondition(bool (*condition)(T)) {
        Node<T>* current = head;
        while (current) {
            if (condition(current->data)) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

// Функція для введення матриці вручну з клавіатури
void inputMatrix(SparseMatrix<int>& matrix, int rows, int cols) {
    std::cout << "Enter matrix elements row-wise:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int element;
            std::cout << "Enter element at position (" << i << ", " << j << "): ";
            std::cin >> element;
            matrix.addElement(element, i, j);
        }
    }
}

int main() {
    // Приклад використання
    int rows, cols;

    std::cout << "Введіть кількість рядків: ";
    std::cin >> rows;
    std::cout << "Введіть кількість стовпців: ";
    std::cin >> cols;

    SparseMatrix<int> matrix;

    inputMatrix(matrix, rows, cols);

    // Доступ за індексом
    std::cout << "Елемент за індексом (0, 0): " << matrix.getElement(0, 0) << std::endl;
    std::cout << "Елемент за індексом (1, 1): " << matrix.getElement(1, 1) << std::endl;

    // Пошук за значенням
    std::cout << "Пошук за значенням 3: " << (matrix.searchByValue(3) ? "Found" : "Not found") << std::endl;
    std::cout << "Пошук за значенням 5: " << (matrix.searchByValue(5) ? "Found" : "Not found") << std::endl;

    // Пошук першого елемента за умовою
    auto condition = [](int value) { return value > 2; };
    Node<int>* result = matrix.searchByCondition(condition);
    if (result) {
        std::cout << "Перший елемент, що задовольняє умову: " << result->data << std::endl;
    } else {
        std::cout << "Елемент, що задовольняє умову, не знайдено." << std::endl;
    }

    return 0;
}
