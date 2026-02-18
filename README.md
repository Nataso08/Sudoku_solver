# 🧩 Sudoku Solver

Un risolutore di Sudoku efficiente e versatile scritto in C++, che utilizza un algoritmo di backtracking ottimizzato per risolvere puzzle Sudoku di qualsiasi dimensione (9x9, 16x16, ecc.).

## ✨ Caratteristiche

- **Dimensioni flessibili**: Supporta Sudoku di diverse dimensioni (9x9, 16x16, 25x25, ecc.)
- **Algoritmo ottimizzato**: Utilizza una strategia di backtracking intelligente che sceglie sempre la cella con il minor numero di opzioni possibili
- **Performance tracking**: Misura e mostra il tempo di esecuzione della risoluzione
- **Input versatile**: Accetta puzzle da console o da file
- **Codice modulare**: Struttura del codice pulita e ben organizzata con classi dedicate

## 🚀 Come Usare

### Prerequisiti

- Compilatore C++ (supporto per C++11 o superiore)
- Sistema operativo: Linux, macOS, o Windows

### Compilazione

```bash
g++ -o sudoku_solver main.cpp src/solve.cpp -std=c++11
```

### Esecuzione

```bash
./sudoku_solver
```

### Formato di Input

Il programma chiederà:
1. La dimensione del Sudoku (es. `9` per un Sudoku 9x9, `16` per un Sudoku 16x16)
2. La griglia del Sudoku riga per riga, usando `0` per le celle vuote

#### Esempio di Input per un Sudoku 9x9:

```
Inserire la dimensione del Sudoku: >>> 9
Inserisci il Sudoku:
0 2 0 6 0 8 0 0 0
5 8 0 0 0 9 7 0 0
0 0 0 0 4 0 0 0 0
3 7 0 0 0 0 5 0 0
6 0 0 0 0 0 0 0 4
0 0 8 0 0 0 0 1 3
0 0 0 0 2 0 0 0 0
0 0 9 8 0 0 0 3 6
0 0 0 3 0 6 0 9 0
```

### Utilizzo del File di Test

Il repository include un file `test.txt` con diversi puzzle di esempio. Puoi usarlo con l'input redirect:

```bash
./sudoku_solver < test.txt
```

## 📂 Struttura del Progetto

```
Sudoku_solver/
├── main.cpp           # Entry point del programma
├── src/
│   ├── solve.h        # Header con definizioni delle classi e funzioni
│   └── solve.cpp      # Implementazione dell'algoritmo di risoluzione
├── test.txt           # File con puzzle di esempio
└── README.md          # Questo file
```

## 🧠 Algoritmo

Il risolutore utilizza un algoritmo di **backtracking ottimizzato** con le seguenti caratteristiche:

### 1. **Classe Cell**
Ogni cella della griglia mantiene:
- La propria posizione (riga, colonna)
- Un set di opzioni valide
- Metodi per gestire e validare i valori

### 2. **Strategia di Risoluzione**
L'algoritmo segue questi passaggi:

1. **Inizializzazione**: Calcola tutte le opzioni valide per ogni cella vuota
2. **Selezione intelligente**: Sceglie la cella con il minor numero di opzioni (euristica MRV - Minimum Remaining Values)
3. **Tentativo**: Inserisce un valore valido nella cella selezionata
4. **Propagazione**: Aggiorna le opzioni delle celle correlate (stessa riga, colonna, e sottograiglia)
5. **Ricorsione**: Ripete il processo sulle celle rimanenti
6. **Backtracking**: Se si raggiunge un vicolo cieco, torna indietro e prova un'altra opzione

### 3. **Ottimizzazioni**
- **Early termination**: Se una cella ha 0 o 1 opzioni, viene risolta immediatamente
- **Constraint propagation**: Le opzioni vengono aggiornate dinamicamente dopo ogni inserimento
- **Restore intelligente**: Quando si fa backtracking, le opzioni vengono ripristinate in modo efficiente

## 📊 Complessità

- **Tempo**: O(9^m) nel caso peggiore, dove m è il numero di celle vuote (molto più veloce nella pratica grazie alle ottimizzazioni)
- **Spazio**: O(n²) per memorizzare la griglia e le strutture di supporto

## 🔧 Funzioni Principali

### `solve()`
Funzione ricorsiva principale che implementa l'algoritmo di backtracking.

### `findBestCell()`
Identifica la cella vuota con il minor numero di opzioni possibili (euristica MRV).

### `Cell::checkPossible(short n)`
Verifica se un numero può essere inserito in una cella secondo le regole del Sudoku.

### `restoreX(const Cell& P, short n)`
Ripristina le opzioni nelle celle correlate dopo un'operazione di backtracking.

## 💡 Esempio di Output

```
Solved:
1 2 7  6 5 8  9 4 3
5 8 3  2 1 9  7 6 4
9 4 6  7 4 3  1 8 2

3 7 1  4 9 2  5 6 8
6 9 2  5 8 7  3 1 4
4 5 8  9 6 1  2 7 3

7 1 4  1 2 5  6 5 8
2 6 9  8 7 4  1 3 6
8 3 5  3 4 6  7 9 1

Execution time: 0.002453 seconds
```

## 🎯 Casi di Test

Il file `test.txt` include puzzle di diverse difficoltà:
- 4 Sudoku 9x9 (facili, medi, difficili)
- 2 Sudoku 16x16 (molto complessi)

## 🤝 Contribuire

I contributi sono benvenuti! Se vuoi migliorare il progetto:

1. Fai un fork del repository
2. Crea un branch per la tua feature (`git checkout -b feature/AmazingFeature`)
3. Commit delle modifiche (`git commit -m 'Add some AmazingFeature'`)
4. Push al branch (`git push origin feature/AmazingFeature`)
5. Apri una Pull Request

## 📝 Possibili Miglioramenti Futuri

- [ ] Interfaccia grafica (GUI)
- [ ] Salvataggio delle soluzioni su file
- [ ] Rilevamento di Sudoku impossibili
- [ ] Generazione casuale di Sudoku validi
- [ ] Supporto per varianti del Sudoku (Sudoku X, Sudoku Samurai, ecc.)
- [ ] Visualizzazione passo-passo della risoluzione
- [ ] Parallelizzazione dell'algoritmo per puzzle molto grandi

## 📜 Licenza

Questo progetto è distribuito sotto licenza libera. Sentiti libero di utilizzarlo, modificarlo e distribuirlo.

## 👨‍💻 Autore

**Nataso08**

## 🙏 Ringraziamenti

Grazie a tutti coloro che hanno contribuito a migliorare questo progetto e alla comunità open source per l'ispirazione continua!

---

⭐ Se questo progetto ti è stato utile, considera di mettergli una stella su GitHub!
