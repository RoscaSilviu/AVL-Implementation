#include <iostream>
#include <vector>
#include "AVL.h"

void merge(Node* source, Node* destination,AVL& avl) {
    if (source == nullptr)
        return;

    avl.insert(source->key);
    merge(source->left, destination, avl);
    merge(source->right, destination, avl);
}

int main()
{
    AVL avlTree;
    AVL avlTree2;
    int choice;
    int key;
    std::vector<int> constrVect;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Construct\n";
        std::cout << "3. Search\n";
        std::cout << "4. Delete\n";
        std::cout << "5. Minimum\n";
        std::cout << "6. Maximum\n";
        std::cout << "7. Print Tree\n";
        std::cout << "8. Clear\n";
        std::cout << "9. Merge\n";
        std::cout << "10. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter the key to insert: ";
            std::cin >> key;
            avlTree.insert(key);
            break;
        case 2:
            std::cout << "Enter the number of elements to construct: ";
            int n;
            std::cin >> n;
            std::cout << "Enter the elements: ";
            constrVect.resize(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> constrVect[i];
            }
            avlTree.construct(constrVect);
            break;
        case 3:
            std::cout << "Enter the key to search: ";
            std::cin >> key;
            if (avlTree.find(key) != nullptr)
                std::cout << "Key found!\n";
            else
                std::cout << "Key not found!\n";
            break;
        case 4:
            std::cout << "Enter the key to delete: ";
            std::cin >> key;
            avlTree.del(key);
            break;
        case 5:
            std::cout << "Minimum: " << avlTree.minim(avlTree.getRoot())->key << std::endl;
            break;
        case 6:
            std::cout << "Maximum: " << avlTree.maxim(avlTree.getRoot())->key << std::endl;
            break;
        case 7:
            std::cout << "Enter the print option (1-4): ";
            int printOption;
            std::cin >> printOption;
            avlTree.print_tree(printOption);
            break;
        case 8:
            avlTree.clear();
            break;
        case 9:
            std::cout << "Enter the elements for the second AVL tree: ";
            constrVect.clear();
            std::cin >> n;
            constrVect.resize(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> constrVect[i];
            }
            avlTree2.construct(constrVect);
            merge(avlTree.getRoot(), avlTree2.getRoot(),avlTree);
            break;
        case 10:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
            break;
        }

        std::cout << std::endl;

    } while (choice != 10);

    return 0;
}


