#include <stdio.h>
#include <string.h>
#include "product.h"


// This function checks if a given reference number exists in the array of products.
// It returns 1 if the reference number is found and 0 otherwise.
int isReferenceExists(Product products[], int numProducts, int reference) {
    // Iterate over each product in the array.
    for (int i = 0; i < numProducts; i++) {
        // Check if the reference number of the current product matches the given reference.
        if (products[i].reference_number == reference) {
            // If the match is found, the function returns 1 to indicate that the reference exists.
            return 1;
        }
    }
    // If no match is found after checking all products, the function returns 0 to indicate that the reference does not exist.
    return 0;
}
// This function checks if a given reference number exists in the array of products.
// It returns 1 if the reference number is found and 0 otherwise.

// This function counts the available capacity in the stock based on the size and quantity of the products.
int countproducts(Product produits[], int numProducts) {
    int capaciteactuel = 0;
  
    // Iterate over each product in the array.
    for (int i = 0; i < numProducts; i++) {
        // Check the size of the product and update the available capacity accordingly.
        if (strcmp(produits[i].size, "petit") == 0) {
            capaciteactuel = capaciteactuel + 1 * produits[i].quantity;
        } else if (strcmp(produits[i].size, "moyen") == 0) {
            capaciteactuel = capaciteactuel + 2 * produits[i].quantity;
        } else if (strcmp(produits[i].size, "grand") == 0) {
            capaciteactuel = capaciteactuel + 4 * produits[i].quantity;
        }
    }
  
    // Calculate and print the remaining available capacity in the stock.
    printf("Il reste %d places libres en stock.\n", 1000 - capaciteactuel);
  
    // Return the remaining available capacity.
    return 1000 - capaciteactuel;
}


// This function adds a new product to the array of products.
void addProduct(Product products[], int *numProducts) {
    Product newProduct;
    // Get the available capacity in the stock.
    int placelibre = countproducts(products, *numProducts);

    printf("\n====== Ajout d'un produit ======\n");
    printf("Nom du produit : ");
    // Validate and read the name of the new product.
    while (scanf("%s", newProduct.name) != 1) {
        printf("Saisie invalide. Veuillez entrer un entier : ");
        while (getchar() != '\n'); // Empty the input buffer.
    }

    // Check the existence of the reference number and read a new one if it already exists.
    do {
        printf("Numéro de référence : ");
        while (scanf("%d", &newProduct.reference_number) != 1) {
            printf("Saisie invalide. Veuillez entrer un entier : ");
            while (getchar() != '\n'); // Empty the input buffer.
        }
        if (isReferenceExists(products, *numProducts, newProduct.reference_number)) {
            printf("La référence existe déjà. Veuillez en choisir une autre.\n");
        }
    } while (isReferenceExists(products, *numProducts, newProduct.reference_number));

    // Validate and read the quantity of the new product.
    printf("Quantité : ");
    while (scanf("%d", &newProduct.quantity) != 1) {
        printf("Saisie invalide. Veuillez entrer un entier : ");
        while (getchar() != '\n'); // Empty the input buffer.
    }

    // Validate and read the price of the new product.
    printf("Prix : ");
    while (scanf("%f", &newProduct.price) != 1) {
        printf("Saisie invalide. Veuillez entrer un nombre : ");
        while (getchar() != '\n'); // Empty the input buffer.
    }

    // Validate and read the size of the new product.
    printf("Taille (petit, moyen, grand) : ");
    do {
        scanf("%s", newProduct.size);
        while (getchar() != '\n'); // Empty the input buffer.

        if (strcmp(newProduct.size, "petit") != 0 && strcmp(newProduct.size, "moyen") != 0 && strcmp(newProduct.size, "grand") != 0) {
            printf("Saisie invalide. Veuillez entrer une bonne taille : ");
            while (scanf("%s", newProduct.size) != 1) {
                printf("Saisie invalide.  ");
                while (getchar() != '\n'); // Empty the input buffer.
            }
        }
    } while (strcmp(newProduct.size, "petit") != 0 && strcmp(newProduct.size, "moyen") != 0 && strcmp(newProduct.size, "grand") != 0);

    // Check if the available capacity in the stock is sufficient for the new product's size and quantity.
    if ((strcmp(newProduct.size, "petit") == 0) && placelibre < newProduct.quantity) {
        printf("Quantité de place atteinte, veuillez réessayer de saisir une valeur inférieure.\n");
    } else if ((strcmp(newProduct.size, "moyen") == 0) && placelibre < 2 * newProduct.quantity) {
        printf("Quantité de place atteinte, veuillez réessayer de saisir une valeur inférieure.\n");
    } else if ((strcmp(newProduct.size, "grand") == 0) && placelibre < 4 * newProduct.quantity) {
        printf("Quantité de place atteinte, veuillez réessayer de saisir une valeur inférieure.\n");
    } else {
        // Add the new product to the array and increment the number of products.
        products[*numProducts] = newProduct;
        (*numProducts)++;
        printf("Produit ajouté avec succès.\n");
    }
}


// This function searches for a product in the array based on its reference number.
void searchProduct(Product products[], int numProducts) {
    int reference;
    // Validate and read the reference number of the product.
    printf("====== Recherche d'un produit ======\n");
    printf("Numéro de référence : ");
    while (scanf("%d", &reference) != 1) {
        printf("Saisie invalide. Veuillez entrer un entier : ");
        while (getchar() != '\n'); // Empty the input buffer.
    }

    // Iterate over each product in the array.
    for (int i = 0; i < numProducts; i++) {
        // Check if the reference number of the current product matches the search reference.
        if (products[i].reference_number == reference) {
            // Print the details of the found product.
            printf("=== Détails du produit ===\n");
            printf("Nom : %s\n", products[i].name);
            printf("Numéro de référence : %d\n", products[i].reference_number);
            printf("Quantité : %d\n", products[i].quantity);
            printf("Prix : %.2f\n", products[i].price);
            printf("Taille : %s\n", products[i].size);
            return; // Stop the function execution after finding the product.
        }
    }

    // If no match is found after checking all products, print a message indicating the product was not found.
    printf("Produit non trouvé.\n");
}

// This function modifies the quantity of a product based on its reference number.
void modifyProductQuantity(Product products[], int numProducts) {
    int reference;
    int newQuantity;
    int placelibre = countproducts(products, numProducts);
// Validate and read the reference number of the product to modify.
    printf("\n=== Modification de la quantité d'un produit ===\n");
    printf("Numéro de référence : ");
    while (scanf("%d", &reference) != 1) {
        printf("Saisie invalide. Veuillez entrer un entier : ");
        while (getchar() != '\n'); // Empty the input buffer.
    }
// Iterate over each product in the array.
    for (int i = 0; i < numProducts; i++) {
        if (products[i].reference_number == reference) {
          // Validate and read the new quantity.
            printf("Quantité actuelle : %d\n", products[i].quantity);
            printf("Nouvelle quantité : ");
            while (scanf("%d", &newQuantity) != 1) {
                printf("Saisie invalide. Veuillez entrer un entier : ");
                while (getchar() != '\n'); // Empty the input buffer.
            }
// Check if the available capacity in the stock is sufficient for the new quantity and size of the product.
            if ((strcmp(products[i].size, "petit") == 0) && placelibre + products[i].quantity < newQuantity) {
                printf("Quantité de place atteinte, veuillez réessayer de saisir une valeur inférieure.\n");
            } else if ((strcmp(products[i].size, "moyen") == 0) && placelibre + 2 * products[i].quantity < 2 * newQuantity) {
                printf("Quantité de place atteinte, veuillez réessayer de saisir une valeur inférieure.\n");
            } else if ((strcmp(products[i].size, "grand") == 0) && placelibre + 4 * products[i].quantity < 4 * newQuantity) {
                printf("Quantité de place atteinte, veuillez réessayer de saisir une valeur inférieure.\n");
            } else {
// Update the quantity of the product.
                products[i].quantity = newQuantity;
                printf("Quantité modifiée avec succès.\n");
            }
            return; // Stop the function execution after modifying the quantity.
        }
    }
  // If no match is found after checking all products, print a message indicating the product was not found.
    printf("Produit non trouvé.\n");
}

// This function displays the products with low stock.
void displayLowStockProducts(Product products[], int numProducts) {
    Product tmp;
    printf("=== Produits à faible stock ===\n");

    for (int i = 0; i < numProducts; i++) {
        if (products[i].quantity == 0) {
  // Printf the details of the products with zero quantity.
            printf("Nom : %s\n", products[i].name);
            printf("Numéro de référence : %d\n", products[i].reference_number);
            printf("Quantité : %d\n", products[i].quantity);
            printf("Prix : %.2f\n", products[i].price);
            printf("Taille : %s\n", products[i].size);
            printf("\n");
        }
    }
// Sort the products in descending order of quantity in the stock.
    for (int i = 0; i < numProducts - 1; i++) {
        for (int j = i + 1; j < numProducts; j++) {
            if (products[i].quantity < products[j].quantity) {
    // Swap the products(tri).
                tmp = products[i];
                products[i] = products[j];
                products[j] = tmp;
            }
        }
    }

    int j = 0;
  // Display the top 5 products with low quantity but does not equal zero.
    for (int i = numProducts - 1; i > 0; i--) {
        if (j < 5 && products[i].quantity != 0) {
    // Print the details of the products.
            printf("Nom : %s\n", products[i].name);
            printf("Numéro de référence : %d\n", products[i].reference_number);
            printf("Quantité : %d\n", products[i].quantity);
            printf("Prix : %.2f\n", products[i].price);
            printf("Taille : %s\n", products[i].size);
            printf("\n");
            j++;
        }
    }
}

// This function finds the index of a product in an array based on its reference number.
int findProductIndex(Product products[], int numProducts, int referenceNumber) {
    int i;
    for (i = 0; i < numProducts; i++) {
        if (products[i].reference_number == referenceNumber) {
  // If the reference number of the product matches the target reference number.
            return i;  //return the index of the product in the array.
        }
    }
    return -1;  // Product not found, the function returns -1.
}

// This function saves the products in the file.
void saveProducts(Product products[], int numProducts) {
  //Open the file in writing mode.
    FILE *file = fopen("products.txt", "w");
  // Check if the file was opened succesfully.
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
  // Write each product's details in the file.
    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s;%d;%d;%.2f;%s\n", products[i].name, products[i].reference_number, products[i].quantity, products[i].price, products[i].size);
    }
    fclose(file); // Close the file.
}

// This function loads the products from a file.
  void loadProducts(Product products[], int *numProducts) {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Fichier non trouvé. Création d'un nouveau fichier.\n");
        return;
    }
  // Initialize the number of products to 0.
    *numProducts = 0;
    // Read product information from the file until the end of the file or the maximum number of products is reached.
    while ((*numProducts < 100) && (fscanf(file, "%[^;];%d;%d;%f;%s\n", products[*numProducts].name, &products[*numProducts].reference_number, &products[*numProducts].quantity, &products[*numProducts].price, products[*numProducts].size) != EOF)) {
        (*numProducts)++;
    }

    fclose(file);
}

// This function displays the details of each product.
void browseProducts(Product product[], int numProduct) {
    for (int i = 0; i < numProduct; i++) {
        printf("%s ; ref : %d ; quantity : %d ; price : %.2f Euro ; size : %s\n", product[i].name, product[i].reference_number, product[i].quantity, product[i].price, product[i].size);
    }
}
