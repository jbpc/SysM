double Status_Cpu(void){
//*************************************************************************************************************************
// Raw data
    double Total_1  = 0;
    double Total_2  = 0;
    double Idle_1   = 0;
    double Idle_2   = 0;
    for (short Loop = 0; Loop < 2; Loop ++){
        char *Content = (char *)calloc(200, sizeof(char));
        if (Content == NULL){
            perror("Content calloc");
            return 0.1;
        }
        if (File_Read("/proc/stat", Content, 200) == 'X'){
            perror("File_Read");
            free(Content);
            return 0.1;
        }
//*************************************************************************************************************************
// Extract
        char *Cursor = Content;
        Cursor += 3;
        while (*(Cursor) == ' '){
            Cursor++;
        }
        long User       = 0;
        long Nice       = 0;
        long System     = 0;
        long Idle       = 0;
        long Iowait     = 0;
        long Irq        = 0;
        long Softirq    = 0;
        long O_1        = 0;
        long O_2        = 0;
        long O_3        = 0;
        sscanf(Cursor, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", &User, &Nice, &System, &Idle, &Iowait, &Irq,
                                                                    &Softirq, &O_1, &O_2, &O_3);
        free(Content);
        if (Loop == 0){
            Total_1	= User + Nice + System + Idle + Iowait + Irq + Softirq + O_1 + O_2 + O_3;
            Idle_1	= Idle;
        }else {
            Total_2	= User + Nice + System + Idle + Iowait + Irq + Softirq + O_1 + O_2 + O_3;
            Idle_2	= Idle;
        }
        Delay(1, 0);
    }
//*************************************************************************************************************************
// Result
    Total_2 -= Total_1;
    Idle_2  -= Idle_1;
    return (100 * ((Total_2 - Idle_2) / Total_2));
}
