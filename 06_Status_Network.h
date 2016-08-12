char Status_Network(long *Network_Sent, long *Network_Received){
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
//*************************************************************************************************************************
// Extract Received
    char *String_Received = (char *)calloc(10, sizeof(char));
    if (String_Received == NULL){
        free(Content);
        return 'X';
    }
    char *Cursor_Content = Content;
    for (short Skip = 0; Skip < 5; Skip++){
        while (*Cursor_Content != '\n')Cursor_Content++;
        Cursor_Content++;
    }
    Cursor_Content += 8;
    while (*Cursor_Content == ' ')Cursor_Content++;
    unsigned short Cursor_Received = 0;
    while (isdigit(*Cursor_Content) != 0){
        *(String_Received + Cursor_Received) = *Cursor_Content;
        Cursor_Received++;
        Cursor_Content++;
    }
    *Network_Received = atol(String_Received);
    free(String_Received);
//*************************************************************************************************************************
// Extract Sent
    for (short Skip = 0; Skip < 3; Cursor_Content++){
        if (*Cursor_Content == ' '){
            while (*Cursor_Content == ' '){
                Cursor_Content++;
            }
            Skip++;
        }
    }
    char *String_Sent = (char *)calloc(10, sizeof(char));
    if (String_Sent == NULL){
        free(Content);
        return 'X';
    }
    unsigned short Cursor_Sent = 0;
    while (isdigit(*Cursor_Content) != 0){
        *(String_Sent + Cursor_Sent) = *Cursor_Content;
        Cursor_Sent++;
        Cursor_Content++;
    }
    *Network_Sent = atol(String_Sent);
    free(String_Sent);
    free(Content);
	return 'V';
}
