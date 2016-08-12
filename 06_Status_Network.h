char Status_Network(double *Network_Sent, double *Network_Received){
//*************************************************************************************************************************
// Raw data
    system("ifstat > Netflow");
    long    File_Size = 200;
    struct  stat Status;
    if (stat("Netflow", &Status) != -1){
        File_Size = Status.st_size;
    }
    char *Content = (char *)calloc(File_Size + 1, sizeof(char));
    if (Content == NULL){
        return 'X';
    }
    if (File_Read("Netflow", Content, File_Size) == 'X'){
        free(Content);
        return 'X';
    }
    char *Cursor_Content = Content;
    for (short Skip = 0; Skip < 5; Skip++){
        while (*Cursor_Content != '\n')Cursor_Content++;
        Cursor_Content++;
    }
//*************************************************************************************************************************
// Extract Received
    char *Network_Received_String = (char *)calloc(20, sizeof(char));
    if (Network_Received_String == NULL){
        free(Content);
        return 'X';
    }
    for (short Loop = 0; Loop < 5; Loop++){
        while (*Cursor_Content != ' ')Cursor_Content++;
        while (*Cursor_Content == ' ')Cursor_Content++;
    }
    unsigned short Cursor_Received = 0;
    while (*Cursor_Content != ' '){
        *(Network_Received_String + Cursor_Received) = *Cursor_Content;
        Cursor_Received++;
        Cursor_Content++;
    }
    if (*(Network_Received_String + strlen(Network_Received_String) - 1) == 'K'){
        char *Temp = (char *)calloc(20, sizeof(char));
        while (Temp == NULL){
            Temp = (char *)calloc(20, sizeof(char));
        }
        strncat(Temp, Network_Received_String, strlen(Network_Received_String) - 1);
        *Network_Received = atol(Temp) * 1024;
        free(Temp);
    }else {
        *Network_Received = atol(Network_Received_String);
    }
    free(Network_Received_String);
//*************************************************************************************************************************
// Extract Sent
    Cursor_Content += 2;
    while (*Cursor_Content != ' ')Cursor_Content++;
    while (*Cursor_Content == ' ')Cursor_Content++;
    char *Network_Sent_String = (char *)calloc(20, sizeof(char));
    if (Network_Sent_String == NULL){
        free(Content);
        return 'X';
    }
    unsigned short Cursor_Sent = 0;
    while (*Cursor_Content != ' '){
        *(Network_Sent_String + Cursor_Sent) = *Cursor_Content;
        Cursor_Sent++;
        Cursor_Content++;
    }
    if (*(Network_Sent_String + strlen(Network_Sent_String) - 1) == 'K'){
        char *Temp = (char *)calloc(20, sizeof(char));
        while (Temp == NULL){
            Temp = (char *)calloc(20, sizeof(char));
        }
        strncat(Temp, Network_Sent_String, strlen(Network_Sent_String) - 1);
        *Network_Sent = atol(Temp) * 1024;
        free(Temp);
    }else {
        *Network_Sent = atol(Network_Sent_String);
    }
    free(Network_Sent_String);
    free(Content);
    return 'V';
}
