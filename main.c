#include <stdio.h>
#include "product.h"
#include "customer.h"

// Function prototypes

void buyproduct(Product products[], int numProducts, Customer customers[], int numCustomers, Customer log);
//With this function the customer can buys a product.
void buyproduct(Product products[], int numProducts, Customer customers[], int numCustomers, Customer log) {
    int id;
    int quantite;
    float total = 0;
    printf("Entrez la référence du produit que vous souhaitez acheter : ");
    scanf("%d", &id);

    int i;
    for (i = 0; i < numProducts; i++) {
        if (products[i].reference_number == id) {
            printf("Entrez la quantité que vous souhaitez acheter : ");
            scanf("%d", &quantite);

            if (quantite <= products[i].quantity) {
                products[i].quantity -= quantite;
                total = products[i].price * quantite;
                printf("Achat effectué avec succès.\n");
            } else {
                printf("La quantité demandée est supérieure à la quantité disponible.\n");
                return;
            }

            
            char fileName[100];
            sprintf(fileName, "%s.txt", log.first_name);
            FILE *file = fopen(fileName, "a");
            if (file == NULL) {
                printf("Aucun achat n'a été effectué.\n");
                return;
            }

            
            fprintf(file, "Référence: %d, Nom: %s, Prix: %.2f, Quantité: %d\n", products[i].reference_number, products[i].name, products[i].price, quantite);

            fclose(file);

            printf("Cela vous fera un total de %.2f$\n", total);
            printf("Achat effectué avec succès. L'historique d'achat a été mis à jour.\n");
            return;
        }
    }

    printf("Le produit avec la référence %d n'a pas été trouvé.\n", id);
}


int saisieEntier(const char *message) {
    int entier;
    printf("%s", message);

    while (scanf("%d", &entier) != 1) {
        printf("Saisie invalide. Veuillez entrer un entier : ");
        while (getchar() != '\n'); //Empty the input buffer.
    }

    return entier;
}

int countproducts(Product produits[], int numProducts);

int main() {
    Product products[100];
    Customer customers[100];
    int numProducts = 0;
    int numCustomers = 0;
    int modeChoice, mainChoice;
    Customer log;
    Customer customer;
    loadProducts(products, &numProducts);
    loadCustomers(customers, &numCustomers);

    do {
        printf("       ╔════════════════╗ \n");
        printf("       ║   CY Library   ║ \n");
        printf("       ║      Shop      ║ \n");
        printf("       ╚════════════════╝ \n");
        printf("=== Gestion de magasin ===\n");
        printf("Mode :\n");
        printf("1. Gestion du stock\n");
        printf("2. Mode client\n");
        printf("3. Quitter\n");
        printf("Choix : ");
        modeChoice = saisieEntier("");
        switch (modeChoice) {
            case 1:
                do {
                    printf("\n=== Gestion du stock ===\n");
                    printf("1. Ajouter un produit\n");
                    printf("2. Rechercher un produit\n");
                    printf("3. Modifier la quantité d'un produit\n");
                    printf("4. Afficher les produits à faible stock\n");
                    printf("5. Afficher le nombre de places restante\n");
                    printf("6. Retour\n");
                    printf("Choix : ");
                    mainChoice = saisieEntier("");

                    switch (mainChoice) {
                        case 1:
                            addProduct(products, &numProducts);
                            saveProducts(products, numProducts);
                            break;
                        case 2:
                            searchProduct(products, numProducts);
                            break;
                        case 3:
                            modifyProductQuantity(products, numProducts);
                            saveProducts(products, numProducts);
                            break;
                        case 4:
                            displayLowStockProducts(products, numProducts);
                            break;
                        case 5:
                            countproducts(products, numProducts);
                            break;
                        case 6:
                            printf("Retour au menu principal.\n");
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                            break;
                    }

                    printf("\n");
                } while (mainChoice != 6);

                break;
            case 2:
                do {
                    printf("\n=== Mode client ===\n");
                    printf("1. Créer un compte\n");
                    printf("2. Se connecter\n");
                    printf("3. Supprimez un son compte\n");
                    printf("4. Retour\n");
                    printf("Choix : ");
                    mainChoice = saisieEntier("");

                    switch (mainChoice) {
                        case 1:
                            addCustomer(customers, &numCustomers);
                            saveCustomers(customers, numCustomers);
                            break;
                        case 2:
                            log = searchCustomer(customers, numCustomers);
                            printf("Vos 3 derniers achats :\n");
                            purchase_history(log);
                            do {
                                printf("\n=== boutique ===\n");
                                printf("1. Afficher les produits en stock\n");
                                printf("2. Acheter un produit\n");
                                printf("3. Voir mon historique d'achat\n");
                                printf("4. Retour\n");
                                printf("Choix : ");
                                mainChoice = saisieEntier("");
                                switch (mainChoice) {
                                    case 1:
                                        browseProducts(products, numProducts);
                                        break;
                                    case 2:
                                        buyproduct(products, numProducts, customers, numCustomers, log);
                                        saveProducts(products, numProducts);
                                        break;
                                    case 3:
                                        purchase_history(log);
                                        break;
                                    case 4:
                                        printf("Retour au menu principal.\n");
                                        break;
                                    default:
                                        printf("Choix invalide. Veuillez réessayer.\n");
                                        break;
                                }
                                printf("\n");
                            } while (mainChoice != 4);
                            break;
                        case 3:
                            deleteCustomer(customers, &numCustomers);
                            saveCustomers(customers, numCustomers);
                            break;
                        case 4:
                            printf("Retour au menu principal.\n");
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                            break;
                    }

                    printf("\n");
                } while (mainChoice != 4);

                break;
            case 3:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }

        printf("\n");
    } while (modeChoice != 3);

    return 0;
}
