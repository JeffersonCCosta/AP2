#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_QUARTERS 4
#define MAX_BRANCHES 10
#define MAX_PRODUCT_NAME 50
#define MAX_BRANCH_NAME 50

typedef struct {
    double sales;
} QuarterSales;

typedef struct {
    char name[MAX_PRODUCT_NAME];
    QuarterSales quarter_sales[MAX_QUARTERS];
} Product;

Product catalog[MAX_PRODUCTS][MAX_QUARTERS][MAX_BRANCHES];
char product_names[MAX_PRODUCTS][MAX_PRODUCT_NAME];
char branch_names[MAX_BRANCHES][MAX_BRANCH_NAME];
int num_products = 0;
int num_branches = 0;

void initializeCatalog() {
    memset(catalog, 0, sizeof(catalog));
}

void menu() {
    printf("==== Menu ====\n");
    printf("1. System Initialization\n");
    printf("2. System Catalog\n");
    printf("3. Branch Catalog\n");
    printf("4. Insert Product/Quarter Sale\n");
    printf("5. Insert Product/Branch Sale\n");
    printf("6. Branch's Best Selling Product\n");
    printf("7. Branch Selling the Most Products\n");
    printf("8. Best Selling Product\n");
    printf("9. Branch with the Most Sales\n");
    printf("10. Best Quarter\n");
    printf("11. Insert New Product\n");
    printf("12. Insert New Branch\n");
    printf("13. Remove Product\n");
    printf("14. Remove Branch\n");
    printf("15. List Products in a Branch\n");
    printf("0. Exit\n");
    printf("=============\n");
}

void option1() {
    printf("Enter the number of products and branches: ");
    scanf("%d %d", &num_products, &num_branches);
    initializeCatalog();
    printf("System initialized successfully!\n");
}

void updateNames(char names[][MAX_PRODUCT_NAME], int max, const char *msg) {
    for (int i = 0; i < max; i++) {
        printf("Enter the name %d: ", i + 1);
        scanf("%s", names[i]);
    }
    printf("%s updated!\n", msg);
}

void option2() {
    updateNames(product_names, num_products, "System Catalog");
}

void option3() {
    updateNames(branch_names, num_branches, "Branch Catalog");
}

void updateSales(int quarter, const char *productName) {
    for (int i = 0; i < num_branches; i++) {
        double sales;
        printf("Enter sales of %s in branch %s in quarter %d: ", productName, branch_names[i], quarter);
        scanf("%lf", &sales);

        for (int j = 0; j < num_products; j++) {
            if (strcmp(product_names[j], productName) == 0) {
                catalog[j][quarter - 1][i].quarter_sales[i].sales = sales;
                printf("Sales of %s in branch %s in quarter %d updated successfully!\n", productName, branch_names[i], quarter);
                return;
            }
        }
        printf("Product not found in the catalog.\n");
    }
}

void option4() {
    int quarter;
    char productName[MAX_PRODUCT_NAME];

    printf("Enter the quarter number (1, 2, 3, or 4): ");
    scanf("%d", &quarter);

    if (quarter < 1 || quarter > 4) {
        printf("Invalid quarter.\n");
        return;
    }

    printf("Enter the product name: ");
    scanf("%s", productName);

    updateSales(quarter, productName);
}

void option5() {
    int branch;
    char productName[MAX_PRODUCT_NAME];

    printf("Enter the branch number (1 to %d): ", num_branches);
    scanf("%d", &branch);

    if (branch < 1 || branch > num_branches) {
        printf("Invalid branch.\n");
        return;
    }

    printf("Enter the product name: ");
    scanf("%s", productName);

    updateSales(1, productName);
}

void printBestSeller(const char *message, int max, int (*calculateSales)(int)) {
    int bestSeller = -1;
    double maxSales = 0;

    for (int i = 0; i < max; i++) {
        double sales = calculateSales(i);
        if (sales > maxSales) {
            maxSales = sales;
            bestSeller = i;
        }
    }

    if (bestSeller != -1) {
        printf("%s: %s\n", message, bestSeller == num_branches ? "None" : branch_names[bestSeller]);
    } else {
        printf("No %s found.\n", message);
    }
}

double calculateProductSales(int product, int branch) {
    double sales = 0;
    for (int i = 0; i < MAX_QUARTERS; i++) {
        sales += catalog[product][i][branch].quarter_sales[branch].sales;
    }
    return sales;
}

double calculateBranchSales(int branch) {
    double sales = 0;
    for (int i = 0; i < num_products; i++) {
        sales += calculateProductSales(i, branch);
    }
    return sales;
}

double calculateQuarterSales(int quarter) {
    double sales = 0;
    for (int i = 0; i < num_products; i++) {
        for (int j = 0; j < num_branches; j++) {
            sales += catalog[i][quarter - 1][j].quarter_sales[j].sales;
        }
    }
    return sales;
}

void option6() {
    printBestSeller("Branch with Best Selling Product", num_branches, calculateBranchSales);
}

void option7() {
    printBestSeller("Branch Selling the Most Products", num_branches, calculateBranchSales);
}

void option8() {
    printBestSeller("Best Selling Product", num_products, calculateProductSales);
}

void option9() {
    printBestSeller("Branch with the Most Sales", num_branches, calculateBranchSales);
}

void option10() {
    printBestSeller("Best Quarter", MAX_QUARTERS, calculateQuarterSales);
}

void option11() {
    if (num_products < MAX_PRODUCTS) {
        printf("Enter the name of the new product: ");
        scanf("%s", product_names[num_products++]);
        printf("New product added successfully!\n");
    } else {
        printf("Product limit reached.\n");
    }
}

void option12() {
    if (num_branches < MAX_BRANCHES) {
        printf("Enter the name of the new branch: ");
        scanf("%s", branch_names[num_branches++]);
        printf("New branch added successfully!\n");
    } else {
        printf("Branch limit reached.\n");
    }
}

void option13() {
    // To be implemented.
}

void removeBranch(int branchToRemove) {
    for (int k = branchToRemove - 1; k < num_branches - 1; k++) {
        strcpy(branch_names[k], branch_names[k + 1]);
        for (int i = 0; i < num_products; i++) {
            for (int j = 0; j < MAX_QUARTERS; j++) {
                catalog[i][j][k] = catalog[i][j][k + 1];
            }
        }
    }
    num_branches--;
}

void option14() {
    int branchToRemove;

    printf("Enter the branch number to be removed (1 to %d): ", num_branches);
    scanf("%d", &branchToRemove);

    if (branchToRemove < 1 || branchToRemove > num_branches) {
        printf("Invalid branch number.\n");
        return;
    }

    removeBranch(branchToRemove);
    printf("Branch removed successfully!\n");
}

void option15() {
    int branchToDisplay;

    printf("Enter the branch number to be listed (1 to %d): ", num_branches);
    scanf("%d", &branchToDisplay);

    if (branchToDisplay < 1 || branchToDisplay > num_branches) {
        printf("Invalid branch number.\n");
        return;
    }

    printf("Products in branch %s:\n", branch_names[branchToDisplay - 1]);
    for (int i = 0; i < num_products; i++) {
        printf("Product: %s\n", product_names[i]);
        for (int j = 0; j < MAX_QUARTERS; j++) {
            printf("Quarter %d: %.2lf\n", j + 1, catalog[i][j][branchToDisplay - 1].quarter_sales[0].sales);
        }
        printf("=============\n");
    }
}

int main() {
    int choice;
    initializeCatalog();

    do {
        menu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                option1();
                break;
            case 2:
                option2();
                break;
            case 3:
                option3();
                break;
            case 4:
                option4();
                break;
            case 5:
                option5();
                break;
            case 6:
                option6();
                break;
            case 7:
                option7();
                break;
            case 8:
                option8();
                break;
            case 9:
                option9();
                break;
            case 10:
                option10();
                break;
            case 11:
                option11();
                break;
            case 12:
                option12();
                break;
            case 13:
                option13();
                break;
            case 14:
                option14();
                break;
            case 15:
                option15();
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}