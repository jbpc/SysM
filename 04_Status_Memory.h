char Status_Memory(long *Total, long *Used){
//*************************************************************************************************************************
// Read file
	char *Content = (char *)calloc(100, sizeof(char));
	if (Content == NULL){
		return 'X';
	}
	if (File_Read("/proc/meminfo", Content, 100) == 'X'){
		free(Content);
		return 'X';
	}
//*************************************************************************************************************************
// Get
// Delaration
	char *Memory_Total = (char *)calloc(20, sizeof(char));
	if (Memory_Total == NULL){
		free(Content);
		return 'X';
	}
	char *Memory_Free = (char *)calloc(20, sizeof(char));
	if (Memory_Free == NULL){
		free(Memory_Total);
		free(Content);
		return 'X';
	}
// Search
	for (short Get_Total = 0, Cursor_Total = 0; Get_Total < 100; Get_Total++){
		if (isdigit(*(Content + Get_Total)) != 0){
			*(Memory_Total + Cursor_Total) = *(Content + Get_Total);
			Cursor_Total++;
		}else if (*(Content + Get_Total) == 'k'){
			Get_Total++;
			for (short Get_Free = Get_Total, Cursor_Free = 0; Get_Free < 100; Get_Free++){
				if (isdigit(*(Content + Get_Free)) != 0){
					*(Memory_Free + Cursor_Free) = *(Content + Get_Free);
					Cursor_Free++;
				}else if (*(Content + Get_Free) == 'k'){
					break;
				}
			}
			break;
		}
	}
// Found
	*Total	= atol(Memory_Total) * 1024;
	*Used	= *Total - (atol(Memory_Free) * 1024);
	free(Memory_Free);
	free(Memory_Total);
	free(Content);
//*************************************************************************************************************************
	return 'V';
}
