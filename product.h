#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    char name[50];
    int reference_number;
    int quantity;
    float price;
    char size[10];
} Product;

void addProduct(Product products[], int *numProducts);
void searchProduct(Product products[], int numProducts);
void modifyProductQuantity(Product products[], int numProducts);
void displayLowStockProducts(Product products[], int numProducts);
int countproducts(Product produits[], int numProducts);
void saveProducts(Product products[], int numProducts);
void loadProducts(Product products[], int *numProducts);
void browseProducts(Product product[],int numProduct);

#endif  // PRODUCT_H