#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//��ǰ ���� ����üü
struct product {
    char name[20];
    int price;
};

// �� ���� ����ü
struct client {
    char name[20]; // ����
    char adress[100];  // �ּ�
    char phone[20]; // ��ȭ��ȣ
};

// �ֹ� ���� ����ü
struct order {
    int id;
    char p_name[20]; // ��ǰ��
    char cli_name[20]; // �� �̸�
    char date[20]; // �ֹ� ��¥
    int quantity; // ����
};

//���
struct product* Product_list = NULL; // ��ǰ ����Ʈ ����
int num_product = 0;

struct client* Client_list = NULL; // �� ����Ʈ ����
int num_client = 0;

struct order* Order_list = NULL; // �ֹ� ����Ʈ ����
int num_order = 0;


void replace_under(char*); //������ _�� �ٲٴ� �Լ�
void replace_space(char*); //_�� �������� �ٲٴ� �Լ�
void product_search_print(int); //�κ� ��ǰ ��� ���
void clilent_search_print(int); //�κ� �� ��� ���
void order_search_print(int); //�κ� �ֹ� ��� ���
void load_list(); //����Ʈ �ҷ�����
void save_list(int); //����Ʈ �����ϱ�
void product_add(); // ��ǰ �߰�
void product_mod(); // ��ǰ ����
void product_del(); // ��ǰ ����
void client_add(); //�� �߰�
void client_mod(); //�� ����
void client_del(); //�� ����
void order_add(); // �ֹ� �߰�
void order_mod(); // �ֹ� ����
void order_del(); //�ֹ� ����
void product_search_manage(); //��ǰ �˻�
void client_search_manage(); //�� �˻�
void order_search_manage(); // �ֹ� �˻�
void list_print(int); //��� ���
void product_manage(); //��ǰ ���� �޴�
void client_mange(); // �� ���� �޴�
void order_manage(); // �ֹ� ���� �޴�
void manage(); //���� �޴�
void search_manage(); //�˻� �޴�


int main() {
    // ���Ͽ��� ��ǰ ����� �о��
    load_list();

    // ��ǰ ���� �޴� ����
    manage();

    // ���α׷� ���� �� ��ǰ ����� ���Ͽ� ����
    for (int i = 1; i <= 3; i++) save_list(i);

    // ���� �޸� ����
    free(Product_list);
    free(Client_list);
    free(Order_list);

    return 0;
}


//������ _�� �ٲٴ� �Լ�
void replace_under(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}

//_�� �������� �ٲٴ� �Լ�
void replace_space(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '_') {
            str[i] = ' ';
        }
    }
}

void product_search_print(int i) {
    printf("��ǰ��: %s\n", Product_list[i].name);
    printf("����: %d\n", Product_list[i].price);
    printf("----------------------------\n");
}

void clilent_search_print(int i) {

    printf("����: %s\n", Client_list[i].name);
    printf("�� �ּ�: %s\n", Client_list[i].adress);
    printf("�޴���ȭ: %s\n", Client_list[i].phone);
    printf("----------------------------\n");
}

void order_search_print(int i) {

    printf("�ֹ� id: %d\n", Order_list[i].id);
    printf("��ǰ��: %s\n", Order_list[i].p_name);
    printf("�ֹ� ����: %d\n", Order_list[i].quantity);
    printf("�ֹ���: %s\n", Order_list[i].cli_name);
    printf("�ֹ� ��¥: %s\n", Order_list[i].date);
    printf("----------------------------\n");

}


// ���Ͽ��� ��ǰ ����� �о��
void load_list() {

    FILE* p_file;
    FILE* c_file;
    FILE* o_file;

    //product ���� �ҷ�����
    p_file = fopen("products.txt", "r");
    if (p_file == NULL) {
        printf("��ǰ ������ �� �� �����ϴ�.\n\n");
        return;
    }

    // ��ǰ ���� ���Ͽ��� �о� ��
    fscanf(p_file, "%d", &num_product);

    Product_list = (struct product*)malloc(sizeof(struct product) * num_product);

    // ��ǰ ������ ���Ͽ��� �о� ��
    for (int i = 0; i < num_product; i++) {
        fscanf(p_file, "%s %d", Product_list[i].name, &(Product_list[i].price));
    }
    fclose(p_file);


    //client ���� �ҷ�����
    c_file = fopen("client.txt", "r");
    if (c_file == NULL) {
        printf("�� ������ �� �� �����ϴ�.\n");
        return;
    }

    // �� ���� ���Ͽ��� �о� ��
    fscanf(c_file, "%d", &num_client);

    Client_list = (struct client*)malloc(sizeof(struct client) * num_client);

    // �� ������ ���Ͽ��� �о� ��
    for (int i = 0; i < num_client; i++) {
        replace_under(Client_list[i].adress); //�ּ� �и� ����
        fscanf(c_file, "%s %s %s", Client_list[i].name, Client_list[i].adress, Client_list[i].phone);
    }
    fclose(c_file);


    //order ���� �ҷ�����
    o_file = fopen("order.txt", "r");
    if (o_file == NULL) {
        printf("��ǰ ������ �� �� �����ϴ�.\n\n");
        return;
    }

    // �ֹ� ���� ���Ͽ��� �о� ��
    fscanf(o_file, "%d", &num_order);

    Order_list = (struct order*)malloc(sizeof(struct order) * num_order);

    // �ֹ� ������ ���Ͽ��� �о� ��
    for (int i = 0; i < num_order; i++) {
        fscanf(o_file, "%d %s %s %s %d", &(Order_list[i].id), Order_list[i].p_name, Order_list[i].cli_name, Order_list[i].date, &(Order_list[i].quantity));
    }
    fclose(o_file);

}

// ��ǰ ����� ���Ͽ� ����
void save_list(int num) {
    // ��ǰ ����� ������ ���� �̸�

    FILE* p_file = NULL;
    FILE* c_file = NULL;
    FILE* o_file = NULL;


    switch (num) {

    case 1:
        p_file = fopen("products.txt", "w");
        if (p_file == NULL) {
            printf("��ǰ ������ �� �� �����ϴ�.\n");
            fclose(p_file);
            fclose(c_file);
            fclose(o_file);
            return;
        }

        // ��ǰ ���� ���Ͽ� ��
        fprintf(p_file, "%d\n", num_product);

        // ��ǰ ������ ���Ͽ� ��
        for (int i = 0; i < num_product; i++) {
            fprintf(p_file, "%s %d\n", Product_list[i].name, Product_list[i].price);
        }
        return;

    case 2:
        c_file = fopen("client.txt", "w");
        if (c_file == NULL) {
            printf("�� ������ �� �� �����ϴ�.\n");
            fclose(p_file);
            fclose(c_file);
            fclose(o_file);
            return;
        }

        // �� ������ ���Ͽ� ��
        fprintf(c_file, "%d\n", num_client);

        // �� ������ ���Ͽ� ��
        for (int i = 0; i < num_client; i++) {
            fprintf(c_file, "%s %s %s\n", Client_list[i].name, Client_list[i].adress, Client_list[i].phone);
            replace_space(Client_list[i].adress);
        }

        return;

    case 3:
        o_file = fopen("order.txt", "w");
        if (o_file == NULL) {
            printf(" ������ �� �� �����ϴ�.\n");
            fclose(p_file);
            fclose(c_file);
            fclose(o_file);
            return;
        }

        // �ֹ� ������ ���Ͽ� ��
        fprintf(o_file, "%d\n", num_order);

        // �� ������ ���Ͽ� ��
        for (int i = 0; i < num_order; i++) {
            fprintf(o_file, "%d %s %s %s %d\n", Order_list[i].id, Order_list[i].p_name, Order_list[i].cli_name, Order_list[i].date, Order_list[i].quantity);
        }
        return;

    default:
        printf("���� �߸��Է��ϼ̽��ϴ�.\n");
        return;

    }
    fclose(p_file);
    fclose(c_file);
    fclose(o_file);
}

// ��ǰ �߰�
void product_add() {
    struct product new_product;

    printf("��ǰ �߰�\n\n");
    printf("��ǰ���� �Է����ּ���: ");
    scanf("%s", new_product.name);

    printf("������ �Է����ּ���: ");
    scanf("%d", &(new_product.price));

    // ��ǰ ��Ͽ� �߰�
    num_product++;
    Product_list = (struct product*)realloc(Product_list, sizeof(struct product) * num_product);
    if (Product_list == NULL) {
        printf("��ǰ ������ �� �� �����ϴ�.\n");
        return;
    }
    Product_list[num_product - 1] = new_product;

    printf("��ǰ�� �߰��Ǿ����ϴ�.\n\n");

    // ����� ��ǰ ����� ���Ͽ� ����
    save_list(1);
}

//��ǰ ����
void product_mod() {
    char product_name[20];
    int select, a = 0, found = 0;

    printf("��ǰ ���� \n");
    printf("������ ��ǰ���� �Է����ּ���: ");
    scanf("%s", product_name);

    for (int i = 0; i < num_product; i++) {
        if (strcmp(Product_list[i].name, product_name) == 0) {
            found = 1;

            while (a == 0) {

                printf("1. ��ǰ��\n");
                printf("2. ��ǰ���\n");
                printf("3. ���� ����\n");
                printf("������ �κ��� �������ּ���: \n");
                scanf("%d", &select);

                switch (select) {

                case 1:
                    printf("��ǰ���� �������ּ���: ");
                    scanf("%s", Product_list[i].name);
                    a = 1;
                    break;

                case 2:
                    printf("��ǰ ��� �������ּ���: ");
                    scanf("%d", &(Product_list[i].price));
                    a = 1;
                    break;

                case 3:
                    printf("��ǰ���� �������ּ���: ");
                    scanf("%s", Product_list[i].name);
                    printf("��ǰ ��� �������ּ���: ");
                    scanf("%d", &(Product_list[i].price));
                    a = 1;
                    break;

                default:
                    printf("�޴��� ���� ��ȣ �Դϴ�. �ٽ� �Է����ּ���.\n");
                }
                if (a == 1) break;
            }
            break;
        }
    }
    if (!found) {
        printf("��ǰ�� ã�� �� �����ϴ�.\n\n");
    }
    save_list(1);
}

// ��ǰ ����
void product_del() {


    if (num_product == 0) {
        printf("������ ��ǰ�� �����ϴ�.\n\n");
        return;
    }

    printf("��ǰ ����\n");
    printf("������ ��ǰ���� �Է����ּ���: ");
    char product_name[20];
    scanf("%s", product_name);

    int found = 0;
    for (int i = 0; i < num_product; i++) {
        if (strcmp(Product_list[i].name, product_name) == 0) {
            found = 1;

            // ������ ��ǰ ������ ��ǰ���� �� ĭ�� ������ �̵�

            for (int j = i; j < num_product - 1; j++) {
                Product_list[j] = Product_list[j + 1];
            }
            num_product--;
            Product_list = (struct product*)realloc(Product_list, sizeof(struct product) * num_product);
            if (Product_list == NULL) {
                printf("product_list�� �޸� ���Ҵ��� ���� �Ͽ����ϴ�.");
                free(Product_list);
                exit(1);
            }
            printf("��ǰ�� �����Ǿ����ϴ�.\n\n");
            break;
        }
    }

    if (!found) {
        printf("��ǰ�� ã�� �� �����ϴ�.\n\n");
    }

    // ����� ��ǰ ����� ���Ͽ� ����
    save_list(1);
}

//�� ���� �߰�
void client_add() {
    struct client new_client;

    printf("�� ���� �߰�\n");
    printf("������ ������ �Է����ּ���: ");
    scanf("%s", new_client.name);
    while (getchar() != '\n'); //\n ����


    printf("������ �ּҸ� �Է����ּ���: ");
    fgets(new_client.adress, sizeof(new_client.adress), stdin);
    new_client.adress[strcspn(new_client.adress, "\n")] = '\0'; //fgets�Լ��� ����ؼ� ���� �޾��� \n�� ����
    replace_under(new_client.adress);


    printf("������ ��ȭ��ȣ�� �Է����ּ���: ");
    scanf("%s", new_client.phone);
    while (getchar() != '\n');

    //�� ���� �߰�
    num_client++;
    Client_list = (struct client*)realloc(Client_list, sizeof(struct client) * num_client);
    if (Client_list == NULL) {
        printf("�� ������ �� �� �����ϴ�.\n");
        return;
    }
    Client_list[num_client - 1] = new_client;

    printf("������ ������ �߰��Ǿ����ϴ�.\n");

    //�� ���� ����� ���Ͽ� ����
    save_list(2);
}

//�� ���� ����
void client_mod() {
    char client_name[20];
    int c_select, b = 0, c_found = 0;

    printf("��ǰ ���� \n");
    printf("������ ������ �Է����ּ���: ");
    scanf("%s", client_name);

    for (int i = 0; i < num_client; i++) {
        if (strcmp(Client_list[i].name, client_name) == 0) {
            c_found = 1;

            while (b == 0) {

                printf("\n1. ����\n");
                printf("2. �ּ�\n");
                printf("3. ��ȭ��ȣ\n");
                printf("4. ���� ����\n");
                printf("������ �κ��� �������ּ���:");
                scanf("%d", &c_select);
                while (getchar() != '\n');

                switch (c_select) {

                case 1:
                    printf("\n������ ������ �������ּ���: ");
                    scanf("%s", Client_list[i].name);
                    while (getchar() != '\n');
                    b = 1;
                    break;

                case 2:
                    printf("\n������ �ּҸ� �������ּ���: ");
                    fgets(Client_list[i].adress, sizeof(Client_list[i].adress), stdin);
                    Client_list[i].adress[strcspn(Client_list[i].adress, "\n")] = '\0'; //fgets�Լ��� ����ؼ� ���� �޾��� \n�� ����
                    replace_under(Client_list[i].adress);
                    b = 1;
                    break;

                case 3:
                    printf("\n������ ��ȭ��ȣ�� �������ּ���: ");
                    scanf("%s", Client_list[i].phone);
                    while (getchar() != '\n');
                    b = 1;
                    break;
                case 4:
                    printf("\n������ ������ �������ּ���: ");
                    scanf("%s", Client_list[i].name);
                    while (getchar() != '\n');

                    printf("\n������ �ּҸ� �������ּ���: ");
                    fgets(Client_list[i].adress, sizeof(Client_list[i].adress), stdin);
                    Client_list[i].adress[strcspn(Client_list[i].adress, "\n")] = '\0'; //fgets�Լ��� ����ؼ� ���� �޾��� \n�� ����
                    replace_under(Client_list[i].adress);

                    printf("\n������ ��ȭ��ȣ�� �������ּ���: ");
                    scanf("%s", Client_list[i].phone);
                    while (getchar() != '\n');
                    b = 1;
                    break;

                default:
                    printf("\n�޴��� ���� ��ȣ �Դϴ�. �ٽ� �Է����ּ���.\n");
                }
                if (b == 1) break;
            }
            break;
        }
    }
    if (!c_found) {
        printf("������ ������ ã�� �� �����ϴ�.\n\n");
    }
    save_list(2);
}

// �� ���� ����
void client_del() {

    int num = 1;

    if (num_client == 0) {
        printf("������ ���� �����ϴ�.\n\n");
        return;
    }

    printf("�� ����\n");
    printf("������ ������ �Է����ּ���: ");
    char client_name[20];
    scanf("%s", client_name);

    int found = 0;
    for (int i = 0; i < num_client; i++) {
        if (strcmp(Client_list[i].name, client_name) == 0) {
            found = 1;

            // ������ �� ������ ������ �� ĭ�� ������ �̵�

            for (int j = i; j < num_client - 1; j++) {
                Client_list[j] = Client_list[j + 1];
            }
            num_client--;
            Client_list = (struct client*)realloc(Client_list, sizeof(struct client) * num_client);
            if (Client_list == NULL) {
                printf("client_list�� �޸� ���Ҵ��� ���� �Ͽ����ϴ�.");
                free(Client_list);
                exit(1);
            }
            printf("���� �����Ǿ����ϴ�.\n\n");
            break;
        }
    }

    if (!found) {
        printf("���� ã�� �� �����ϴ�.\n\n");
    }
    save_list(2);
}

// �ֹ� ���� �߰�
void order_add() {
    struct order new_order;
    srand(time(NULL));

    printf("\n��ǰ���� �Է����ּ���: ");
    scanf("%s", new_order.p_name);

    printf("\n�ֹ��ڸ� �Է����ּ���: ");
    scanf("%s", new_order.cli_name);

    printf("\n������ �Է����ּ���: ");
    scanf("%d", &(new_order.quantity));

    printf("\n�ֹ�id�� �������� �߰��˴ϴ�.\n");
    new_order.id = rand() % 10000000;

    printf("�ֹ� ��¥�� ���� ��¥�� �߰��˴ϴ�.\n ");
    //�ֹ� ��¥
    time_t currentTime;
    time(&currentTime);
    struct tm* timeInfo = localtime(&currentTime);
    char timeString[50];
    strftime(timeString, sizeof(timeString), "%Y/%m/%d", timeInfo);
    strcpy(new_order.date, timeString);

    // ��ǰ ��Ͽ� �߰�
    num_order++;
    Order_list = (struct order*)realloc(Order_list, sizeof(struct order) * num_order);
    if (Order_list == NULL) {
        printf("\n�ֹ� ������ �� �� �����ϴ�.\n");
        return;
    }
    Order_list[num_order - 1] = new_order;

    printf("\n�ֹ��� �Ϸ�Ǿ����ϴ�.\n\n");

    // ����� ��ǰ ����� ���Ͽ� ����
    save_list(3);
}

//�ֹ� ���� ����
void order_mod() {
    char order_name[20];
    int select, a = 0, found = 0;

    printf("�ֹ� ���� \n");
    printf("������ id�� �Է����ּ���: ");
    scanf("%s", order_name);

    for (int i = 0; i < num_order; i++) {
        if (strcmp(Order_list[i].id, order_name) == 0) {
            found = 1;

            while (a == 0) {

                printf("1. ��ǰ��\n");
                printf("2. �ֹ��ڸ�\n");
                printf("3. id\n");
                printf("4. ����\n");
                printf("������ �κ��� �������ּ���: \n");
                scanf("%d", &select);

                switch (select) {

                case 1:
                    printf("��ǰ���� �������ּ���: ");
                    scanf("%s", Order_list[i].p_name);
                    a = 1;
                    break;

                case 2:
                    printf("�ֹ��ڸ��� �������ּ���: ");
                    scanf("%s", Order_list[i].cli_name);
                    a = 1;
                    break;

                case 3:
                    printf("id�� �������ּ���: ");
                    scanf("%d", &Order_list[i].id);
                    a = 1;
                    break;

                case 4:
                    printf("��ǰ ��� �������ּ���: ");
                    scanf("%d", &(Order_list[i].quantity));
                    a = 1;
                    break;

                default:
                    printf("�޴��� ���� ��ȣ �Դϴ�. �ٽ� �Է����ּ���.\n");
                }
                if (a == 1) break;
            }
            break;
        }
    }
    if (!found) {
        printf("id�� ã�� �� �����ϴ�.\n\n");
    }
    save_list(3);
}

// �ֹ� ���� ����
void order_del() {

    int num = 1;
    int order_id;

    if (num_order == 0) {
        printf("������ �ֹ��� �����ϴ�.\n\n");
        return;
    }

    printf("�ֹ� ����\n");
    printf("������ id�� �Է����ּ���: ");
    scanf("%d", &order_id);

    int found = 0;
    for (int i = 0; i < num_order; i++) {
        if (Order_list[i].id == order_id) {
            found = 1;

            // ������ �ֹ� ������ �ֹ����� �� ĭ�� ������ �̵�

            for (int j = i; j < num_order - 1; j++) {
                Order_list[j] = Order_list[j + 1];
            }
            num_order--;
            Order_list = (struct order*)realloc(Order_list, sizeof(struct order) * num_order);
            if (Order_list == NULL) {
                printf("order_list�� �޸� ���Ҵ��� ���� �Ͽ����ϴ�.");
                free(Order_list);
                exit(1);
            }
            printf("�ֹ��� �����Ǿ����ϴ�.\n\n");
            break;
        }
    }

    if (!found) {
        printf("�ֹ��� ã�� �� �����ϴ�.\n\n");
    }
    save_list(3);
}

//��ǰ �˻�
void product_search_manage() {

    char search_t[20];
    int choice, s_price, found;

    while (1) {
        printf("----------------------------\n\n");
        printf("�˻��� �׸��� �������ּ���\n\n");
        printf("0. �޴��� ���ư���\n");
        printf("1. ��ǰ��\n");
        printf("2. ��ǰ ����\n");
        printf("�Է�: ");
        scanf("%d", &choice);

        switch (choice) {

        case 0:
            return;

        case 1:
            printf("\n�˻��� ��ǰ���� �Է����ּ���: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_product; i++) {
                if (strcmp(Product_list[i].name, search_t) == 0) {
                    found = 1;
                    product_search_print(i);

                }
            }
            if (!found) printf("�˻� ����� �����ϴ�.\n\n");

            found = 0;

            break;

        case 2:
            printf("\n�˻��� ������ �Է����ּ���: ");
            scanf("%d", &s_price);
            for (int i = 0; i < num_product; i++) {
                if (Product_list[i].price == s_price) {
                    found = 1;
                    product_search_print(i);
                }
            }
            if (!found) printf("\n�˻� ����� �����ϴ�.\n\n");

            found = 0;

            break;

        default:
            printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n\n");
            break;
        }

    }

}


//�� �˻�
void client_search_manage() {

    char search_t[20];
    int choice, found;

    while (1) {
        printf("----------------------------\n\n");
        printf("\n�˻��� �׸��� �������ּ���\n\n");
        printf("0. �޴��� ���ư���\n");
        printf("1. ����\n");
        printf("2. �� �ּ�\n");
        printf("3. ��ȭ ��ȣ\n");
        printf("�Է�: ");
        scanf("%d", &choice);

        switch (choice) {

        case 0:
            return;

        case 1:
            printf("\n�˻��� ������ �Է����ּ���: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_client; i++) {
                if (strcmp(Client_list[i].name, search_t) == 0) {
                    found = 1;
                    clilent_search_print(i);
                }
            }
            if (!found) printf("\n�˻� ����� �����ϴ�.\n\n");

            found = 0;

            break;

        case 2:
            printf("\n�˻��� �ּҸ� �Է����ּ���: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_client; i++) {
                if (strcmp(Client_list[i].adress, search_t) == 0) {
                    found = 1;
                    clilent_search_print(i);
                }
            }
            if (!found) printf("\n�˻� ����� �����ϴ�.\n\n");

            found = 0;

            break;

        case 3:
            printf("\n�˻��� ��ȭ��ȣ�� �Է����ּ���: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_client; i++) {
                if (strcmp(Client_list[i].phone, search_t) == 0) {
                    found = 1;
                    clilent_search_print(i);
                }
            }
            if (!found) printf("\n�˻� ����� �����ϴ�.\n\n");

            found = 0;

            break;

        default:
            printf("\n�߸��� �Է��Դϴ�. �ٽ��Է����ּ���.\n\n");
            break;
        }
    }

}



//�ֹ� �˻�
void order_search_manage() {

    char search_t[20];
    int choice, found, isearch_t;

    while (1) {
        printf("----------------------------\n\n");
        printf("\n�˻��� �׸��� �������ּ���\n\n");
        printf("0. �޴��� ���ư���\n");
        printf("1. ��ǰ��\n");
        printf("2. �ֹ���\n");
        printf("3. �ֹ� ��¥\n");
        printf("4. �ֹ� id\n");
        printf("�Է�: ");
        scanf("%d", &choice);

        switch (choice) {

        case 0:
            return;

        case 1:
            printf("\n�˻��� ��ǰ���� �Է����ּ���: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_order; i++) {
                if (strcmp(Order_list[i].p_name, search_t) == 0) {
                    found = 1;
                    order_search_print(i);
                }
            }
            if (!found) printf("\n�˻� ����� �����ϴ�.\n\n");

            found = 0;

            break;

        case 2:
            printf("\n�˻��� �ֹ��ڸ��� �Է����ּ���: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_order; i++) {
                if (strcmp(Order_list[i].cli_name, search_t) == 0) {
                    found = 1;
                    order_search_print(i);
                }
            }
            if (!found) printf("\n�˻� ����� �����ϴ�.\n\n");

            found = 0;

            break;

        case 3:
            printf("�˻��� �ֹ� ��¥�� �Է����ּ���: ");
            scanf("%s", search_t);
            for (int i = 0; i < num_order; i++) {
                if (strcmp(Order_list[i].date, search_t) == 0) {
                    found = 1;
                    order_search_print(i);
                }
            }
            if (!found) printf("\n�˻� ����� �����ϴ�.\n\n");

            found = 0;

            break;

        case 4:
            printf("�˻��� �ֹ� id�� �Է����ּ���: ");
            scanf("%d", &isearch_t);
            for (int i = 0; i < num_order; i++) {
                if (Order_list[i].id == isearch_t) {
                    found = 1;
                    order_search_print(i);
                }
            }
            if (!found) printf("\n�˻� ����� �����ϴ�.\n\n");

            found = 0;

            break;


        default:
            printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n\n");
            break;
        }

    }


}



//��� ���
void list_print(int num) {

    switch (num) {

    case 1:
        printf("��ǰ ���\n\n");
        printf("----------------------------\n\n");
        for (int i = 0; i < num_product; i++) {
            printf("��ǰ��: %s\n", Product_list[i].name);
            printf("����: %d\n\n", Product_list[i].price);
            printf("----------------------------\n\n");
        }
        break;

    case 2:
        printf("�� ���\n\n");
        printf("----------------------------\n\n");
        for (int i = 0; i < num_client; i++) {
            printf("��ǰ��: %s\n", Client_list[i].name);
            printf("�ּ�: %s\n", Client_list[i].adress);
            printf("�޴���ȭ: %s\n\n", Client_list[i].phone);
            printf("----------------------------\n\n");
        }
        break;

    case 3:
        printf("�ֹ� ���\n\n");
        printf("----------------------------\n\n");
        for (int i = 0; i < num_order; i++) {
            printf("�ֹ� id: %d\n", Order_list[i].id);
            printf("��ǰ��: %s\n", Order_list[i].p_name);
            printf("�ֹ��ڸ�: %s\n", Order_list[i].cli_name);
            printf("��¥: %s\n", Order_list[i].date);
            printf("�ֹ� ����: %d\n\n", Order_list[i].quantity);
            printf("----------------------------\n\n");
        }
        break;
    }

}// ����

//���� �޴�
void product_manage() {
    int choice;

    while (1) {
        printf("----------------------------\n\n");
        printf("1. ��ǰ �߰� �޴�\n");
        printf("2. ��ǰ ���� �޴�\n");
        printf("3. ��ǰ ���� �޴�\n");
        printf("4. ��ǰ ��� ���\n");
        printf("5. �޴��� ���ư���\n");
        printf("0. ����\n");
        printf("�޴��� �����ϼ���: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            exit(1);
        case 1:
            product_add();
            break;

        case 2:
            product_mod();
            break;

        case 3:
            product_del();
            break;

        case 4:
            list_print(1);
            break;

        case 5:
            return;

        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
            break;
        }
    }
}

void client_manage() {
    int choice;

    while (1) {
        printf("----------------------------\n\n");
        printf("1. �� �߰� �޴�\n");
        printf("2. �� ���� �޴�\n");
        printf("3. �� ���� �޴�\n");
        printf("4. �� ��� ���\n");
        printf("5. �޴��� ���ư���\n");
        printf("0. ����\n");
        printf("�޴��� �����ϼ���: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            exit(1);
        case 1:
            client_add();
            break;

        case 2:
            client_mod();
            break;

        case 3:
            client_del();
            break;

        case 4:
            list_print(2);
            break;

        case 5:
            return;

        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
            break;
        }
    }
}

void order_manage() {
    int choice;

    while (1) {
        printf("----------------------------\n\n");
        printf("1. �ֹ� �߰� �޴�\n");
        printf("2. �ֹ� ���� �޴�\n");
        printf("3. �ֹ� ���� �޴�\n");
        printf("4. �ֹ� ��� ���\n");
        printf("5. �޴��� ���ư���\n");
        printf("0. ����\n");
        printf("�޴��� �����ϼ���: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            exit(1);
        case 1:
            order_add();
            break;

        case 2:
            order_mod();
            break;

        case 3:
            order_del();
            break;

        case 4:
            list_print(3);
            break;

        case 5:
            return;

        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
            break;
        }
    }
}

void manage() {
    int choice;

    while (1) {
        printf("----------------------------\n\n");
        printf("1. ��ǰ �޴�\n");
        printf("2. �� �޴�\n");
        printf("3. �ֹ� �޴�\n");
        printf("4. �˻� �޴�\n");
        printf("0. ����\n");
        printf("�޴��� �����ϼ���: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            exit(1);
        case 1:
            product_manage();
            break;

        case 2:
            client_manage();
            break;

        case 3:
            order_manage();
            break;

        case 4:
            search_manage();

        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
            break;
        }
    }
}

void search_manage() {

    int choice;

    while (1) {
        printf("----------------------------\n\n");
        printf("�˻� �� ������ �������ּ���\n");
        printf("0. �޴��� ���ư���\n");
        printf("1. ��ǰ ����\n");
        printf("2. �� ����\n");
        printf("3. �ֹ� ����\n");
        printf("�Է�: ");
        scanf("%d", &choice);

        switch (choice) {

        case 0:
            return;

        case 1:
            product_search_manage();
            break;

        case 2:
            client_search_manage();
            break;

        case 3:
            order_search_manage();
            break;

        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
            break;
        }
    }
}