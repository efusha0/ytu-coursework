# 📦 Cargo Shipment Tracking System (Sorted Linked List & File I/O in C)

A lightweight logistics and shipment management console application developed in the **C programming language**. This project demonstrates dynamic memory allocation, sorted singly linked list manipulation, and automated multi-file generation to process and categorize shipping records.

## 📌 About the Project

Logistics companies require organized, structured systems to monitor shipments, track delivery statuses, and generate statistical reports. Designed as a core systems programming exercise, this software reads raw shipment data from a text file, structures it into memory using custom structs, and dynamically maintains a **sorted linked list ordered by tracking codes**.

Beyond simply organizing data in memory, the application acts as an automated report generator—parsing the linked list to output personalized customer notification files, filtered status logs, and city-wide delivery analytics.

---

## 🚀 Key Features & Functionality

* **📥 Automated Data Ingestion & Sorting:**
  * Reads shipment records (Sender Name, Tracking Code, Destination City, Shipping Day, and Delivery Status) from an input text file (`kargolar.txt`).
  * Dynamically allocates nodes and inserts them into a singly linked list using a **Sorted Insertion Algorithm** based on the numerical/alphabetical tracking code.

* **🖥️ Console Visualization:**
  * Traverses the sorted linked list to display a clean, tabulated overview of all shipment records directly on the console.

* **🗂️ Multi-File Report Generation:**
  * **Personalized Sender Logs (`[Name].txt`):** Automatically generates individual text files for each sender (e.g., `Elif.txt`), listing only their specific shipment histories and statuses.
  * **Pending Shipments Filter (`bekleyenler.txt`):** Filters the linked list to extract and save all shipments currently marked as `"Beklemede"` (Pending/Waiting).
  * **City-Wide Analytics (`rapor.txt`):** Aggregates data across the entire list to generate a comprehensive statistical summary showing the total number of delivered (`"TeslimEdildi"`) vs. pending shipments per destination city.

---

## 🛠️ Technical Concepts Demonstrated

* **Custom Data Structures (`struct`):** Modeling real-world shipping entities with encapsulated attributes.
* **Dynamic Memory Allocation:** Efficient use of `malloc()` for node creation and `free()` for complete memory deallocation to prevent memory leaks.
* **Linked List Algorithms:** Implementing sorted insertion without relying on post-read array sorting algorithms.
* **File Input/Output (I/O):** Extensive use of file streams (`fopen`, `fscanf`, `fprintf`, `fclose`) in both read (`"r"`) and write (`"w"`) modes.
* **String Manipulation:** Handling and comparing textual data (`strcmp`, `strcpy`) for city aggregation and sender grouping.

---

## ▶️ Build and Run

```bash
gcc cargo_tracking.c -o cargo_tracking
./cargo_tracking
```

The program reads `kargolar.txt` from the working directory. Each line describes one shipment:

```text
<senderID> <trackingCode> <senderName> <city> <day> <status>
```

`<status>` is either `TeslimEdildi` (delivered) or `Beklemede` (pending). A small sample `kargolar.txt` is included.

Running the program prints the sorted list and writes one `<Name>.txt` file per sender, `bekleyenler.txt` and `rapor.txt` into the working directory. These generated files are not kept in the repository. Sender files are opened in append mode, so delete them before running the program again.
