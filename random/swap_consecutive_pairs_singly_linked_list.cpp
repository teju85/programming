struct List {
    int data;
    List* next;
};


List* swap_consec(List* head) {
    if(head == NULL) {
        return head;
    }
    List* first = head;
    List* second = first->next;
    if(second == NULL) {
        return first;
    }
    List* temp = second->next;
    second->next = first;
    first->next = swap_consec(temp);
    return second;
}
