#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct {
    char first_name[50];
    char last_name[50];
    float purchase_history;
} Customer;

void addCustomer(Customer customers[], int *numCustomers);
Customer searchCustomer(Customer customers[], int numCustomers);
void deleteCustomer(Customer customers[], int *numCustomers);
void saveCustomers(Customer customers[], int numCustomers);
void loadCustomers(Customer customers[], int *numCustomers);
void purchase_history(Customer log);

#endif  // CUSTOMER_H
