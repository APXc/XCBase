# XCBase - Simple Encryption/Decryption Tool

XCBase è un semplice strumento di crittografia che permette di criptare e decriptare messaggi usando diversi algoritmi.

## Funzionalità

- **Criptaggio Semplice**: Algoritmo di cifratura Caesar migliorato
- **Decriptaggio Semplice**: Decifratura del criptaggio semplice
- **Gestione File**: Lettura e criptaggio/decriptaggio di file di testo
- **Criptaggio Sicuro**: Crittografia XOR con chiave casuale
- **Decriptaggio Sicuro**: Decifratura del criptaggio sicuro con chiave (Nuovo!)

## Compilazione

### Usando Makefile
```bash
make
```

### Compilazione manuale
```bash
g++ -std=c++17 -Wall -Wextra -O2 xc_improved.cpp -o xcbase
```

## Utilizzo

Esegui il programma:
```bash
./xcbase
```

Scegli una delle opzioni disponibili:
1. **Criptaggio Semplice (1)**: Cripta una stringa usando l'algoritmo Caesar
2. **Decriptaggio Semplice (2)**: Decripta una stringa criptata con l'algoritmo Caesar
3. **Gestione da File (3)**: Legge un file e lo cripta/decripta
4. **Criptaggio Sicuro (4)**: Usa crittografia XOR con chiave casuale
5. **Decriptaggio Sicuro (5)**: Decripta testo criptato con il modo sicuro usando la chiave

## File di Output

- `report.txt`: Contiene il risultato dell'ultima operazione
- `log.txt`: Registro delle operazioni eseguite
- `key.txt`: Chiave per il criptaggio sicuro (solo con opzione 4)

## Utilizzo del Criptaggio/Decriptaggio Sicuro

### Criptaggio Sicuro (Opzione 4)
1. Inserisci il testo da criptare
2. Il sistema genera automaticamente una chiave casuale
3. Il testo viene criptato usando XOR e scrambling
4. La chiave viene salvata in `key.txt` e il testo criptato in `report.txt`

### Decriptaggio Sicuro (Opzione 5)
1. Inserisci il testo criptato (es. da `report.txt`)
2. Scegli come fornire la chiave:
   - Inserisci `0` per leggere automaticamente da `key.txt`
   - Inserisci il numero della chiave manualmente
3. Il testo viene decriptato e salvato in `report.txt`

## Test

Esegui i test automatici:
```bash
make test
```

## Miglioramenti nella Versione 0.6 (2025)

- ✅ Risolti problemi di codifica dei file (UTF-16 → UTF-8)
- ✅ Compatibilità cross-platform (Windows/Linux/macOS)
- ✅ Correzione di buffer overflow e memory leak
- ✅ Aggiunto criptaggio sicuro con XOR e chiave casuale
- ✅ Migliore gestione degli errori
- ✅ Input sicuro contro buffer overflow
- ✅ Aggiunto sistema di build con Makefile
- ✅ Documentazione migliorata

## Sicurezza

⚠️ **Nota Importante**: Questo è un progetto educativo. Per applicazioni di produzione, usa librerie crittografiche standard come OpenSSL.

- Il **criptaggio semplice** usa un algoritmo Caesar modificato (facile da decifrare)
- Il **criptaggio sicuro** usa XOR con chiave casuale (più sicuro ma non a livello militare)

## Requisiti

- Compilatore C++ con supporto C++17
- Sistema operativo: Windows, Linux, macOS

## Licenza

Mozilla Public License Version 2.0
