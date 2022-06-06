#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define M 5 // 5, 7, 9 ���� �Է½� �� level�� ���� Ʈ���� �� �׷���
#define max_children M
#define max_keys max_children-1
#define min_keys (int)(ceil(M/2.0))-1 // �ּ� Ű����

struct B_Tree {
    bool leaf; // leaf���� 
    int key[max_keys + 1]; // key�� ���� �迭
    int check_key; // Ű ���� Ȯ�ο�
    struct B_Tree* child[max_children + 1]; // �ڽ� �����͹迭 (������ �迭��)
    int check_child; // �ڽ� ���� Ȯ�ο�
};

int RemoveValueInNode(int val, struct B_Tree* node);

struct B_Tree* root; // root ��� �⺻ ����(�����ͷ�)


// �޾ƿ��� ���� �ִ� ������
struct B_Tree* createNode(int val) {
    struct B_Tree* node; // ���ο� node ����ü ����
    node = (struct B_Tree*)malloc(sizeof(struct B_Tree)); // node�� �����Ҵ�
    node->leaf = false; // ó���� �������δ� �ʱⰪ false��
    node->key[0] = val; // �� node�� 1��° key ���� �޾ƿ� ������ �ֱ�
    node->check_key = 1;
    node->check_child = 0;
    return node;
}

// ����� ���� �и��ؼ� �ٸ� ��忡 �й��ϴ� �Լ�
struct B_Tree* splitNode(int position, struct B_Tree* node, struct B_Tree* parent) { // ���� ���, �θ� ���, �����忡�� ���� ���� ��ġ�� �˰��ִ� pos�� ���ڷ� �ޱ�
    int median; // �и� ���� �߾Ӱ�
    median = node->check_key / 2; // �߾Ӱ��� ¦���̵� Ȧ���̵� Ű����/2��
    struct B_Tree* right_node; // ���� �ڽ��� �� ������ ���

    right_node = (struct B_Tree*)malloc(sizeof(struct B_Tree));
    right_node->leaf = node->leaf; // �и��� �ѰŴϱ� ���� �и��Ϸ��� ���� ���� ���ΰ� ����.
    right_node->check_key = 0;
    right_node->check_child = 0;

    int num_iter = node->check_key;
    for (int i = median + 1; i < num_iter; i++) { // �и��� ��忡 Ű ���
        right_node->key[i - (median + 1)] = node->key[i];
        right_node->check_key++;
        node->check_key--;
    }

    if (!node->leaf) { // ���� ��尡 ������ �ƴϸ�, �ڽ� ���
        num_iter = node->check_child;
        for (int i = median + 1; i < num_iter; i++) { // ������ ��忡 ���� ��� �ڽ� ���� ���
            right_node->child[i - (median + 1)] = node->child[i];
            right_node->check_child++; // ���� ä���� ����� �ڽ� ������ ����, ���� ��忡���� ����
            node->check_child--;
        }
    }

    // �и��� �� ���� �ø� �θ� ��� ó��
    if (node == root) { // ��Ʈ�� �� �θ� ��� ������ ��. 
        struct B_Tree* new_parent_node;
        new_parent_node = createNode(node->key[median]); // �߾Ӱ� ������ �� �θ� ��� �����
        node->check_key--;
        new_parent_node->child[0] = node; // ���θ����� ���� �ڽ��� ���� ���
        new_parent_node->child[1] = right_node;

        new_parent_node->check_child = 2;
        return new_parent_node;
    }
    else { // ��Ʈ�� �ƴϸ�, ���� �ִ� �θ��� Ȱ��
        for (int i = parent->check_key; i > position; i--) { // �θ����� Ű ��ġ �ٽ��ϱ�
            parent->key[i] = parent->key[i - 1];
            parent->child[i + 1] = parent->child[i];
        }

        parent->key[position] = node->key[median]; // �θ� ��忡 �־�ߵ� �ڸ��� �� �ֱ�
        parent->check_key++; // �θ��忡 ���� �־����ϱ� Ű���� �߰�, ���� ���� Ű ���� ���̱�
        node->check_key--;
        parent->child[position + 1] = right_node; // ���� ���� ���� ����Ǿ������� �����ʸ� �θ��忡 ����.
        parent->check_child += 1;
    }
    return node; //���� ��� ����
}


struct B_Tree* insertNode(int ParentPosition, int value, struct B_Tree* node, struct B_Tree* parent) { // ������ ��,  
    int pos; // ���� ��忡�� Ű�� ��ġ�� ���� �־�� ��. �ֳĸ� �������� �ϴ� ���� ��ġ�� ã�ƾ� �ϱ� ����.
    for (pos = 0; pos < node->check_key; pos++) {// pos ��ġ�� 0���� �ؼ�, ���� ����� Ű ������ŭ Ž��
        if (value == node->key[pos]) { // node�� pos��° Ű�� val�� ������
            printf("Duplicates are not permitted!\n");
            return node;
        }
        else if (value < node->key[pos]) { // val�� node�� pos��° Ű���� ������ �� pos���� �����.
            break;
        }
    }// ���� val�� �� node�� �ִ� ������ ũ�� �翬�� ������ pos�� ���� ����.
    if (!node->leaf) { // node leaf ���ΰ� false�̸�, leaf�� �ƴϸ�
        node->child[pos] = insertNode(pos, value, node->child[pos], node); // node�� pos��° �ڽ� ��忡 insertNode ���� ��´�. ��ͷ� �ڽ��� Ž���ϱ� ���� �� ��.
        if (node->check_key == max_keys + 1) { // ���� ��� Ű ������ ��Ģ���� ����Ű�����
            node = splitNode(ParentPosition, node, parent); // �� �������� �и��� �ؾ� ��.
        }
    }
    else { // leaf�� ���� ���� ����
        for (int i = node->check_key; i > pos; i--) { // ���������� val�� �����ؾ� �ϴ� ��ġ�� �ִ� �������� ������ �ڷ� ����� �۾��� �Ѵ�.
            node->key[i] = node->key[i - 1]; // Ű�� �ڷ� �� ĭ�� ���� �۾�.
            node->child[i + 1] = node->child[i]; // �ڽĵ� ��������.
        }

        node->key[pos] = value; // val�� �����ؾ� �ϴ� ��ġ�� val ����.
        node->check_key++; // �ϳ� ���������� Ű ���� ����
        if (node->check_key == max_keys + 1) { // leaf ��尡 �� á���� �и��� ���ش�.
            node = splitNode(ParentPosition, node, parent);
        }
    }
    return node; // node�� ���� �־��ִϱ� �� node�� ��ȯ�ؾ� ��. �׷��� ��� ����Ǿ ���� ��� ����.

}


void insert(int value) {
    if (!root) { // root�� ������
        root = createNode(value); // root����
        root->leaf = true; // ó�� ��������°Ŵϱ� root���� leaf ���.
        return;
    }
    else { // ��Ʈ�� �ִٸ�..
        root = insertNode(0, value, root, root); // ó������ root�� �θ����� �������.
    }
}
// ���� �Լ�
void mergeNode(struct B_Tree* Pnode, int nodePosition, int MnodePosition) {

    int merge_idx = Pnode->child[MnodePosition]->check_key; // merge�� ��ü ����ʿ� merge�� Ű ��ġ�� �����Ѵ�.
    Pnode->child[MnodePosition]->key[merge_idx] = Pnode->key[MnodePosition]; //�θ����� Ű�� merge��.
    Pnode->child[MnodePosition]->check_key++;

    for (int i = 0; i < Pnode->child[nodePosition]->check_key; i++) { // ����� ��忡�� �� Ű�� ������ �ּ� Ű ���� ������ �ȵ� �� ����. ���� Ű ���� merge�� ���� �Űܾ� ��. ����Ű�� ������ �ƿ� for���� �ȵ��ư�.
        Pnode->child[MnodePosition]->key[merge_idx + 1 + i] = Pnode->child[nodePosition]->key[i]; // Ű ������ 2�� -> i�� 0, merge idx ������ Ű/ Ű ������ �þ�� i�� �ϳ��� �� �þ. 
        Pnode->child[MnodePosition]->check_key++;
    }

    int merge_childidx = Pnode->child[MnodePosition]->check_child; //merge�� ��� ���κ����� �Űܾ� �ϴ� ���κ� idx ����.
    for (int i = 0; i < Pnode->child[nodePosition]->check_child; i++) { // ����� ��忡�� Ű�� ����� ���� �ڽ��� ������. �³׸� merge�� ���� �Űܾ� �Ѵ�.
        Pnode->child[MnodePosition]->child[merge_childidx + i] = Pnode->child[nodePosition]->child[i];
        Pnode->child[MnodePosition]->check_child++;
    }

    free(Pnode->child[nodePosition]); // merge �ǰ� ���� �ݴ��� ���� �ʿ������ �޸𸮿��� ������

    for (int i = MnodePosition; i < (Pnode->check_key) - 1; i++) { //�θ� ����� Ű �ϳ��� �̹� �ڽ� ���� ���յǾ����� �������ؾ� ��.
        Pnode->key[i] = Pnode->key[i + 1];
    }
    Pnode->check_key--;

    for (int i = MnodePosition + 1; i < (Pnode->check_child) - 1; i++) { // �θ� ��忡�� ���� �� �� ���� �� �ڿ� �ٸ� �ڽĵ� ���� �� ������ ��迭 �ؾ� ��. merge�� ��� �� ������ ����� ��.
        Pnode->child[i] = Pnode->child[i + 1];
    }
    Pnode->check_child--;
}

// ���ʿ��� ������ �Լ�
void borrowFromLeft(struct B_Tree* Pnode, int CnodePosition) { // �θ� ���� ���� ��� pos��ġ�� ���ڷ� ����. �̹� ���� ����� Ű�� ��������. cnt_key�� �ּһ��� Ȥ�� �̸��ϰ���.
    int tenant_idx = 0; // ������ ��ü��忡 �����ִ� Ű�� ������ ��ġ.

    // ������ ���� �ڸ��� �����ؾ� �ϱ� ������ �����ִ°Ÿ� ��ĭ �� �ڷ� �̷�� ��.(�����ִ°� ��� ����). borrowFromRight�� �ٸ��� ���� �ڸ� ������ �ؾ� ��.
    for (int i = 0; i < Pnode->child[CnodePosition]->check_key; i++) {
        Pnode->child[CnodePosition]->key[i + 1] = Pnode->child[CnodePosition]->key[i];
    }
    Pnode->child[CnodePosition]->key[tenant_idx] = Pnode->key[CnodePosition - 1]; // ������ Ű�� �������� �� �θ𿡰Լ� �����´�. ���⼭�� ���ʿ��� �������ϱ�, cur_node_pos(������ �ڽ� ����Ű�� ��ġ)���� 1�� ���� �θ��� Ű ��ġ�� ��. �׸��� ��������� Ű�� ���� �ö󰡴� ��.
    Pnode->child[CnodePosition]->check_key++;

    int idx_from_sib_topar = (Pnode->child[CnodePosition - 1]->check_key) - 1; // �θ��� Ű�� ������ �������ϱ� ���� ��� �� ������ Ű�� �ϳ� �θ�� �÷��� ��. 
    Pnode->key[CnodePosition - 1] = Pnode->child[CnodePosition - 1]->key[idx_from_sib_topar]; // �θ���� ������ ��������� Ű�� ���´�. ���⼱ ���� �������.
    Pnode->child[CnodePosition - 1]->check_key--;

    // �������� Ű�� ���������� �ڽĵ� ������ �ؾ���. �ڽ� ��ġ ������ ����.(�� ĭ�� ������ �����)
    if (Pnode->child[CnodePosition - 1]->check_child > 0) { // ���� ��� �ڽ��� �ִ� ��쿡��
        int tenant_childidx = (Pnode->child[CnodePosition - 1]->check_child) - 1; // tenant ��忡�ٰ� ��������� ���� �� �ڽ� ��ġ�� ��ߵǱ� ������ �� �ε��� ����.
        // �ڽ� ��ġ ����. borrowFromRight�� �ٸ��� �ű�� �� �̸� �����ؾ� ��. 
        for (int i = Pnode->child[CnodePosition]->check_child; i > 0; i--) { // �ڿ������� �����ؼ� �տ��� �ڷ� �ű�� ����.
            Pnode->child[CnodePosition]->child[i] = Pnode->child[CnodePosition]->child[i - 1];
        }

        Pnode->child[CnodePosition]->child[0] = Pnode->child[CnodePosition - 1]->child[tenant_childidx]; // ���� ��� �ڽ� ������. ������ �ڽ� ���� ��ġ�� ���� ����� 1��° ��ġ.
        Pnode->child[CnodePosition]->check_child++;

        Pnode->child[CnodePosition - 1]->check_child--;
    }
}

// �����ʿ��� ������ �Լ�
void borrowFromRight(struct B_Tree* Pnode, int CnodePosition) { // �θ� ���� ���� ��� pos��ġ�� ���ڷ� ����. �̹� ���� ����� Ű�� ��������. cnt_key�� �ּһ��� Ȥ�� �̸��ϰ���.
    int tenant_idx = Pnode->child[CnodePosition]->check_key; // ������ ��ü��忡 �����ִ� Ű�� ������ ��ġ.
    Pnode->child[CnodePosition]->key[tenant_idx] = Pnode->key[CnodePosition]; // ������ Ű�� �������� �� �θ𿡰Լ� �����´�. �׸��� ��������� Ű�� ���� �ö󰡴� ��.
    Pnode->child[CnodePosition]->check_key++;

    int idx_from_sib_topar = 0;
    Pnode->key[CnodePosition] = Pnode->child[CnodePosition + 1]->key[idx_from_sib_topar]; // �θ���� ������ ��������� Ű�� ���´�.

    // // �������� Ű�� ���������ϱ� ��ġ ������ �ؾ� �Ѵ�.(�� ĭ�� ������ �����)
    for (int i = 0; i < (Pnode->child[CnodePosition + 1]->check_key) - 1; i++) {
        Pnode->child[CnodePosition + 1]->key[i] = Pnode->child[CnodePosition + 1]->key[i + 1];
    }
    Pnode->child[CnodePosition + 1]->check_key--;

    int idx_from_sib = 0;
    // �������� Ű�� ���������� �ڽĵ� ������ �ؾ���. �ڽ� ��ġ ������ ����.(�� ĭ�� ������ �����)
    if (Pnode->child[CnodePosition + 1]->check_child > 0) { // �ڽ��� �ִ� ��쿡��
        int tenant_childidx = Pnode->child[CnodePosition]->check_child; // tenant ��忡 ������ �ڽ��� �� ��ġ
        Pnode->child[CnodePosition]->child[tenant_childidx] = Pnode->child[CnodePosition + 1]->child[idx_from_sib]; // ���� ��� �ڽ� ������.
        Pnode->child[CnodePosition]->check_child++;

        // �ڽ� ��ġ ���� 
        for (int i = 0; i < Pnode->child[CnodePosition + 1]->check_child - 1; i++) {
            Pnode->child[CnodePosition + 1]->child[i] = Pnode->child[CnodePosition + 1]->child[i + 1];
        }
        Pnode->child[CnodePosition + 1]->check_child--;
    }
}

void balanceNode(struct B_Tree* node, int childPosition) { // ���� ���� �ڽĳ�忡���� ��ġ�� ���ڷ� �޴� �Լ�(������,������ ����)
    if (childPosition == 0) { // �ڽĳ�� Ű ��ġ�� �� �����϶��� ������ �θ�,������ ���� ��.
        if (node->child[childPosition + 1]->check_key > min_keys) { // (�ڽĳ�� ����) ������ Ű������ �ּҼ��� ���� �� �μ�����
            borrowFromRight(node, childPosition);
        }
        else { // ������ Ű������ �ּҼ��� ���� �μ�����
            mergeNode(node, childPosition + 1, childPosition); // �θ���(������)�� �ڽ� ��ġ�� �ڱ� ���� ��ġ�� ���� �Ѱ���.  
        }
        return;
    }

    else if (childPosition == (node->check_key)) { // �ڽĳ�� Ű ��ġ�� �� �������� ���� ���� �θ�, ���� ���� ��.
        if (node->child[childPosition - 1]->check_key > min_keys) { // �ڽĳ�� ����, ���� ������ Ű������ �ּҼ��� ���� �� �μ��� ��
            borrowFromLeft(node, childPosition);
        }
        else { // �ּҼ��� ���� �μ��� ��
            mergeNode(node, childPosition, childPosition - 1); // �θ���(������)�� ����� ���� ���մ�� ��� ��ġ�� ���� �Ѱ���.  
        }
        return;
    }
    else { // �� ����,�� ������ ���� �� �̿�
        if (node->child[childPosition - 1]->check_key > min_keys) {
            borrowFromLeft(node, childPosition);
        }
        else if (node->child[childPosition + 1]->check_key > min_keys) {
            borrowFromRight(node, childPosition);
        }
        else {
            mergeNode(node, childPosition, childPosition - 1); // �شܿ� �ִ� �ڽ� ���� �� �� ������ ��ġ�� ������ ������ ��
        }
        return;
    }
}

// ���γ�� �������� �ڽĵ��� merge�ؾ��ϴ� ���̽�
int mergeChildNode(struct B_Tree* Pnode, int CnodePostition) {
    int mergeidx = Pnode->child[CnodePostition]->check_key; // merge�� ���� �������� �ϴµ� �ڽĳ�忡�� ������ ��ġ ����.
    // �ٷ� ������ �ʰ� ��ġ���� �ϴ� ��忡 ������� �ϴ� �θ���(���γ��)�� ���� ��ħ. �ֳ�? �� ������ �ٷ� ����� �ڽĳ�常 ��ġ��, ��ġ���� �ϴ� ��� �ؿ� �� �ڽĳ�尡 ���� ��쿡�� �ڽ� 1���� �������� ��. 
    // �׷��� �ϴ� �θ����� ���� �ְ� �ű⼭ �� ��ͷ� ���� �� �ڽ��� ��ġ���� �������� �ؼ� �ڽļ��� �ذ��ؾ� ��.
    int val_par_node = Pnode->key[CnodePostition]; // ������� �θ� ����� ���� ���
    Pnode->child[CnodePostition]->key[mergeidx] = Pnode->key[CnodePostition];
    Pnode->child[CnodePostition]->check_key++;

    // ��ġ���� ��忡 ���� ��� ���� ������ ��. (���� �Լ��� ����)
    for (int i = 0; i < Pnode->child[CnodePostition + 1]->check_key; i++) {
        Pnode->child[CnodePostition]->key[mergeidx + 1 + i] = Pnode->child[CnodePostition + 1]->key[i];
        Pnode->child[CnodePostition]->check_key++;
    }
    // ������� �ڽĵ� ���;� ��.
    for (int i = 0; i < Pnode->child[CnodePostition + 1]->check_child; i++) {
        Pnode->child[CnodePostition]->child[mergeidx + 1 + i] = Pnode->child[CnodePostition + 1]->child[i];
        Pnode->child[CnodePostition]->check_child++;
    }

    // �θ���(���γ��)�� Ű�� �����ϱ� ��迭 & �ڽĵ� ��迭
    for (int i = CnodePostition; i < Pnode->check_key; i++) {
        Pnode->key[i] = Pnode->key[i + 1];
        Pnode->check_key--;
    }
    for (int i = CnodePostition + 1; i < Pnode->check_child; i++) {
        Pnode->child[i] = Pnode->child[i + 1];
        Pnode->check_child--;
    }
    return val_par_node; // �θ��忡�� ���ȴ� ���� ����� ���� �ϴ� ����. ���� �����ϴ� �Լ����� ������ ����.

}

// predecessor ã�� �Լ�
int findPredecessor(struct B_Tree* Cnode) {
    int predecessor;
    if (Cnode->leaf) { //���� Ž����尡 �����̸�, ã�� �� ����.
        return Cnode->key[Cnode->check_key - 1]; //���� ��忡�� ���� ū Ű �ָ� ��.(predecessor ����)
    }
    return findPredecessor(Cnode->child[(Cnode->check_child) - 1]); // Ž���� ������ ū �� �ڽ����� Ž���ؾ� ��.
}
// predecessor ã�Ƽ� ���γ�忡 ������ �Լ�
int overrideWithPredecessor(struct B_Tree* par_node, int pos_std_search) {
    int predecessor = findPredecessor(par_node->child[pos_std_search]); // predecessor�� ��ͷ� �� �������� ã�� �Լ� ȣ��. �θ� ���� Ÿ�� ������ ��ġ�� ���ڷ� ��.
    par_node->key[pos_std_search] = predecessor; // ������� �ϴ� ���γ���� ���� ã�� predecessor�� ��ü ����.
    return predecessor;
}

// suceessor ã�� �Լ�
int findSuccessor(struct B_Tree* Cnode) {
    int successor;
    if (Cnode->leaf) { //���� Ž����尡 �����̸�, ã�� �� ����.
        return Cnode->key[0]; //���� ��忡�� ���� ���� Ű �ָ� ��.(successor ����)
    }
    return findSuccessor(Cnode->child[0]); // Ž���� ������ ���� �� �ڽ����� Ž���ؾ� ��.
}
// successor ã�Ƽ� ���γ�忡 ������ �Լ�
int overrideWithSuccessor(struct B_Tree* par_node, int pos_std_search) {
    int successor = findSuccessor(par_node->child[pos_std_search + 1]); // successor�� ��ͷ� �� �������� ã�� �Լ� ȣ��. �θ� ���� Ÿ�� ������ ��ġ(���������� ���ߵ�.)�� ���ڷ� ��.
    par_node->key[pos_std_search] = successor; // ������� �ϴ� ���γ���� ���� ã�� successor�� ��ü ����.
    return successor;
}

// ���� ��忡�� ���� ����� �Լ�
void deleteInnerNode(struct B_Tree* Cnode, int CnodePosition) {
    int cessor = 0; // predecessor Ȥ�� successor�� ���� ��� || merge�� ����� ã�� ���� ���� ����
    int deletion_for_merge = 0;
    // ���� ������ �� ����� �ڽ��� �� ������ Ȯ��, predeȤ�� successor�� ã�ƾ� �ϱ⶧��. ���� ������ ������ ���� ���� ����.
    if (Cnode->child[CnodePosition]->check_key >= Cnode->child[CnodePosition + 1]->check_key) {
        if (Cnode->child[CnodePosition]->check_key > min_keys) { // �ڽ� Ű������ �ּҹ��� �ν��� ������ predecessor ã�� ����.
            cessor = overrideWithPredecessor(Cnode, CnodePosition);
            RemoveValueInNode(cessor, Cnode->child[CnodePosition]); // ã�� predecessor�� ���� �÷��� ��. �ٵ� �� ������ �ᱹ �ش� ������忡�� ���� ����°� ȿ���� �����ϴ� �Լ� ȣ��.
        }
        else {
            deletion_for_merge = mergeChildNode(Cnode, CnodePosition);
            RemoveValueInNode(deletion_for_merge, Cnode->child[CnodePosition]);
        }
    }
    else {
        if (Cnode->child[CnodePosition + 1]->check_key > min_keys) {
            cessor = overrideWithSuccessor(Cnode, CnodePosition);
            RemoveValueInNode(cessor, Cnode->child[CnodePosition + 1]); // successor ã���� �̰͵� ������忡�� ����� ȿ���� ���� ��.
        }
        else {
            deletion_for_merge = mergeChildNode(Cnode, CnodePosition);
            RemoveValueInNode(deletion_for_merge, Cnode->child[CnodePosition]);
        }

    }

}// ���� ����� ���� �־��ָ� ����� �Լ�.
int RemoveValueInNode(int val, struct B_Tree* node) {
    int pos; // ������� ����� ������ ��ġ�� ����.    
    int flag = false; // ���������� ���θ� �˱� ���� flag�� ����
    for (pos = 0; pos < node->check_key; pos++) { // val�� ���������ϴ� �� ��ġ�� ã�ƾ� ��.���� ����� Ű ������ŭ Ž��
        if (val == node->key[pos]) { // ���� ����� Ű �迭���� pos�� val�� ������
            flag = true; // ã�Ҵٴ� ǥ��
            break;
        }
        else if (val < node->key[pos]) { // Ű �迭�� pos ��ġ ���� val���� ũ�� �� ��ġ���� �����. �ű⿡�� �Ʒ��� �� ���� �Ѵ�.
            break;
        }
    } // �̰� �����ٴ°� �� ��忡�� (�߰� Ž����) pos��ġ�� �������ٴ� �� 
    if (flag) { // flag�� true�̸� ������ �����ϴ� �۾� �ǽ�
        if (node->leaf) {  // �������� �����ؾ� �ϸ�
            for (int i = pos; i < node->check_key; i++) { // ����� pos��ġ���� Ű ������ŭ Ž��
                node->key[i] = node->key[i + 1]; // ������� Ű ��ġ�� �� ���� Ű�� �����
            }
            node->check_key--;
        }
        else { // ���ο��� �����ؾ� �ϸ�
            deleteInnerNode(node, pos); //���� ����� ���� �����ϴ� �Լ� ����. ���� ���� �����忡���� �� ��ġ�� ���ڷ� �ѱ�.
        }
        return flag;
    }
    else { // flag�� false�̸�(������� ���� ��ã�� ��)
        if (node->leaf) { //leaf ����̸�
            return flag;
        }
        else { // ������� ���� �� ã�Ҵµ� ���� ����̸� �� ������.
            flag = RemoveValueInNode(val, node->child[pos]); //val�̶� �������� pos��° �ڽ� �Ѱܼ� flag �ޱ�
        }
    }
    if (node->child[pos]->check_key < min_keys) { // (��Ͱ� ������ �ٽ� �ö�µ�)����ó���ߴ� �ڽ� ����� Ű ������ �ּҼ��� ���� �μ����� ��
        balanceNode(node, pos); // ������, �����ϴ� �ϴ� �Լ� ���� (���� ���� �ڽĳ���� pos��ġ�� ���ڷ�)
    }

    return flag;
}

// ����� �Լ�
void dodelete(struct B_Tree* node, int val) { // ���� ������� ��

    int flag = RemoveValueInNode(val, node); // ���� ��� ������ ���� ����� �Լ� ȣ��. ����� ���̶� ���� ��带 ���ڷ� ����. ������ flag�� ����.
    if (!flag) { // flag�� 0�̸� ����.
        printf("%d does not exist in this tree. \n", val); // �Լ� ������ ��ã���� �÷��װ� 0�ΰŴϱ� ���� �޼��� ���
        return;
    }
    if (node->check_key == 0) {  // deleteVal�� �ϰ� ���� node�� Ű������ 0�� �� = ���� ��忡 �ƹ��͵� ��� ��ȭ�� �ʿ���.
        node = node->child[0]; // ���� ��带 ���� ���� �ڽ� ���� ����.
    }
    root = node;

}// Ʈ�� ����Ʈ �ϴ� �Լ�
void printBTree(struct B_Tree* node, int level) {
    printf("%d��° �� :   ", level);
    for (int i = 0; i < level - 1; i++) {
        printf("            "); // Ʈ�� ������ ����� ���� ����
    }
    for (int i = 0; i < node->check_key; i++) {
        printf("%d ", node->key[i]);
    }
    printf("\n");
    level++;
    for (int i = 0; i < node->check_child; i++) {
        printBTree(node->child[i], level);
    }
}

int k[1000];
int main(void) {
    time_t start, end;
    double result;

    // test
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        k[i] = -1;
    }
    
    for (int i = 0; i < 1000; i++) { // ������ �ߺ��� ������ 
        k[i] = rand() % 10000;
        int temp = k[i];
        for(int j = 0; j < i; j++) {
            if (k[j] == temp) {
                i--;
            }
        }
    }
    start = time(NULL);
    for (int i = 0; i < 1000; i++) { //  0-9999 ������ �ߺ����� ������ 1000���� ����
        insert(k[i]);
    }
    for (int i = 0; i < 500; i++) { // ������ 500���� �����ϴ� ������ ����
        dodelete(root,k[i]);
    }
    end = time(NULL); // �ð� ���� ��
    result = (double)(end - start);
    printf("B-Tree 1000�� ����, 500�� ���� �ð� : %f��\n\n\n", result); // 1000�� ����, 500�� ���� ���� ����

    printBTree(root, 1); // level 1���� M���� ������ ���ڱ����� level�� B-tree�� ������



    return 0;
}