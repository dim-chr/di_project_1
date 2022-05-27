# Vectors Nearest Neighbors and Clustering

Ομάδα:</br>
Δημήτρης Χριστοφής      1115201800214</br>
Κωνσταντίνος Θεοφίλης   1115201600287

Αναζήτηση και συσταδοποίηση διανυσμάτων με χρήση C++

Δομή αρχείων project:
Το project είναι υλοποιημένο και χωρισμένο σε modules. Ότι αφορά κώδικα βρίσκεται στον φάκελο /src, ο οποίος με την σειρά του χωρίζεται σε 4 υποφακέλους 
ανάλογα με τα ερωτήματα. Σημείωση: ο φάκελος /src/Common περιλαμβάνει κώδικα κοινό και για τις τρεις υλοποιήσεις που ζητούνται. 
Στο root του /src βρίσκονται τρία αρχεία με main, ένα για την κάθε εκτέλεση. Τα προγραμματα μας μεταγλωττίζονται με χρήση Makefile. 

Μεταγλώττιση και εκτέλεση:

LSH:
    - compile with: `make lsh`
    - execute with: `./lsh -i ./dir/input_small_id -q ./dir/query_small_id -o outputfile.txt -N <int> -k <int> -L <int> -R <int>`

CUBE:
    - compile with: `make cube`
    - execute with: `./cube -i ./dir/input_small_id -q ./dir/query_small_id -o outputfile.txt -N <int> -k <int> -probes <int> -R <int> -M <int>`

CLUSTER: 
    - compile with: `make cluster`
    - execute with: `./cluster -i ./dir/input_small_id -c ./dir/cluster.conf -o outputfile.txt -complete [optional] -m [Classic or LSH or Hypercube]`
