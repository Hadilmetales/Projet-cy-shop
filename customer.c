#include <stdio.h>
#include <string.h>
#include "customer.h"

// This function checks if a customer with the given ID exists in the array of customers.
int isCustomersExists(Customer customers[], int numCustomers, char id[50]) {
    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(customers[i].first_name, id) == 0) {
            return 1; // Return 1 if the cutomer ID exist.
        }
    }
    return 0; // Return 0 is the customer ID does not exist.
}

// This function adds a new customer 
void addCustomer(Customer customers[], int *numCustomers) {
    Customer newCustomer;

    printf("=== Ajout d'un client ===\n");

    // Checking the existence of the ID.
    do {
        printf("ID de connexion : ");
        while (scanf("%s", newCustomer.first_name) != 1) {
            printf("Saisie invalide. Veuillez entrer un nombre : ");
            while (getchar() != '\n'); // Empty the input buffer.
        }

        if (isCustomersExists(customers, *numCustomers, newCustomer.first_name)) {
            printf("L'ID existe déjà. Veuillez en choisir un autre.\n");
        }
    } while (isCustomersExists(customers, *numCustomers, newCustomer.first_name));

    printf("Mot de passe : ");
    while (scanf("%s", newCustomer.last_name) != 1) {
        printf("Saisie invalide. Veuillez entrer un nombre : ");
        while (getchar() != '\n'); // Empty the input buffer.
    }

    printf("\n");

    customers[*numCustomers] = newCustomer; // Add the new customer at the end of the array.
    (*numCustomers)++; // Increment the total number of customers.

    printf("Client ajouté avec succès.\n");
}

// This function searches for a customer in the array based on its ID.
Customer searchCustomer(Customer customers[], int numCustomers) {
    Customer custom;

    printf("=== Recherche d'un client ===\n");
    printf("ID de connexion : ");
    while (scanf("%s", custom.first_name) != 1) {
        printf("Saisie invalide. Veuillez entrer un nombre : ");
        while (getchar() != '\n'); //Clearing input buffer.
    }

    printf("Mot de passe : ");
    while (scanf("%s", custom.last_name) != 1) {
        printf("Saisie invalide. Veuillez entrer un nombre : ");
        while (getchar() != '\n'); 
    }
// Iterate over each customer in the array.
    for (int i = 0; i < numCustomers; i++) {
      // Searching for a matching customer.
      // Comparing the entered ID and password with the customer's ID and password.
        if (strcmp(customers[i].first_name, custom.first_name) == 0 && strcmp(customers[i].last_name, custom.last_name) == 0) {
            printf("=== Détails du client ===\n");
            printf("ID de connexion : %s\n", customers[i].first_name);
            printf("Mot de passe : %s\n", customers[i].last_name);
            return customers[i];
        }
    }

    printf("Client non trouvé.\n");
}

// This function deletes a customer.
void deleteCustomer(Customer customers[], int *numCustomers) {
    char firstName[50];
    char lastName[50];

    printf("=== Suppression d'un client ===\n");
    printf("ID de connexion : ");
    while (scanf("%s", firstName) != 1) {
        printf("Saisie invalide. Veuillez entrer un nombre : ");
        while (getchar() != '\n'); //Empty input buffer.
    }

    printf("Mot de passe : ");
    while (scanf("%s", lastName) != 1) {
        printf("Saisie invalide. Veuillez entrer un nombre : ");
        while (getchar() != '\n'); //Empty input buffer.
    }

    int found = 0;
// Searching for a matching customer.
    for (int i = 0; i < *numCustomers; i++) {
        if (strcmp(customers[i].first_name, firstName) == 0 && strcmp(customers[i].last_name, lastName) == 0) {
            
            for (int j = i; j < *numCustomers - 1; j++) {
                customers[j] = customers[j + 1];
            }
            (*numCustomers)--;  // Decreasing the total number of customers.
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Client supprimé avec succès.\n");
    } else {
        printf("Client non trouvé.\n");
    }
}

// This function saves the cutomers in a file.
void saveCustomers(Customer customers[], int numCustomers) {
    FILE *file = fopen("customers.txt", "w");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
// Iterate over each customer in the array.
    for (int i = 0; i < numCustomers; i++) {
        fprintf(file, "%s,%s\n", customers[i].first_name, customers[i].last_name);
    }

    fclose(file);
}


void loadCustomers(Customer customers[], int *numCustomers) {
  // Open the file in reading mode.
    FILE *file = fopen("customers.txt", "r");

    if (file == NULL) {
        printf("Fichier de clients introuvable.\n");
        return;
    }

    char line[256];
    int i = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%s\n", customers[i].first_name, customers[i].last_name);
      // Extracting customer informations from each line and storing it in the customers array.
        i++;
    }

    *numCustomers = i; // Updating the total number of customers.

    fclose(file);
}

// This function displays the purchase history of a customer.
void purchase_history(Customer log) {
    char fileName[100];
    sprintf(fileName, "%s.txt", log.first_name); // Creating the file name based on the customer's first name.
    FILE *file = fopen(fileName, "r"); //Opening the file in reading mode.
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'historique d'achat.\n");
        return;
    }

    
    int lineCount = 0;
    char ch;
  // Counting the number of lines in the file.
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }
    fseek(file, 0, SEEK_SET); // Resetting the file pointer to the beginning of the file.

    
    int startLine = (lineCount >= 3) ? (lineCount - 3) : 0;  // Determining the starting line based on whether the line count is greater than or equal to 3.

    
    for (int i = 0; i < startLine; i++) {
      //Skiping lines until the starting line is reached.
        while ((ch = fgetc(file)) != '\n') {
            if (ch == EOF) {
                fclose(file);
                return;
            }
        }
    }

    
    char line[256];
   // Printing the purchase history starting from the start line.
    for (int i = startLine; i < lineCount; i++) {
        fgets(line, 256, file);
        printf("%s", line);
    }

    fclose(file);
}
