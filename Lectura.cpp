 /*
    if (argc != 2){
        cout << "Debe introducir un archivo\n";
        return 1;
    }
    ifstream myfile;
    string line;
    int cant_arcos = 0;
    string delimiter = " ";
    size_t pos = -1;
    string token_1, token_2;
    myfile.open(argv[1]);
    getline(myfile,line)
    pos = line.find(delimiter);
    token_1 = line.substr(0, pos);
    int n=atoi(token_1);
    int m=atoi(line);
    while (getline(myfile,line)){
        cant_arcos+=1;
        pos = line.find(delimiter);
        token_1 = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        pos = line.find(delimiter);
        token_2 = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        cout << token_1 << " "<< token_2 << " "<< line << endl;
    }
    myfile.close();
    return 0;
    */
    