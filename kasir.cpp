#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

// ===================
// Struktur Data Barang
// ===================
struct Barang
{
    string kode;
    string nama;
    double harga;
};

// =====================
// Linked List Belanjaan
// =====================
struct Node
{
    Barang barang;
    Node *next;
};

class LinkedList
{
public:
    Node *head;

    LinkedList() : head(nullptr) {}

    void tambahBarang(Barang b)
    {
        Node *baru = new Node{b, nullptr};
        if (!head)
            head = baru;
        else
        {
            Node *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = baru;
        }
    }

    void tampilkanBarang()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->barang.nama << " - Rp" << temp->barang.harga << endl;
            temp = temp->next;
        }
    }

    double hitungTotal()
    {
        double total = 0;
        Node *temp = head;
        while (temp)
        {
            total += temp->barang.harga;
            temp = temp->next;
        }
        return total;
    }

    void hapusTerakhir()
    {
        if (!head)
            return;
        if (!head->next)
        {
            delete head;
            head = nullptr;
            return;
        }
        Node *temp = head;
        while (temp->next->next)
            temp = temp->next;
        delete temp->next;
        temp->next = nullptr;
    }
};

// ==============
// Tree Kategori
// ==============
struct KategoriNode
{
    string nama;
    KategoriNode *kiri;
    KategoriNode *kanan;

    KategoriNode(string n) : nama(n), kiri(nullptr), kanan(nullptr) {}
};

void inOrderKategori(KategoriNode *node)
{
    if (node)
    {
        inOrderKategori(node->kiri);
        cout << node->nama << " ";
        inOrderKategori(node->kanan);
    }
}

bool cariKategori(KategoriNode *node, string target)
{
    if (!node)
        return false;
    if (node->nama == target)
        return true;
    return cariKategori(node->kiri, target) || cariKategori(node->kanan, target);
}

// ======================
// Program Utama (Kasir)
// ======================
int main()
{
    // 1. Tipe Data & Variabel
    int pilihan;
    string namaPelanggan;
    queue<string> antrean;
    stack<Barang> undoStack;
    LinkedList belanja;

    // 2. Array (Daftar Barang)
    Barang daftarBarang[3] = {
        {"B01", "Susu", 15000},
        {"B02", "Roti", 10000},
        {"B03", "Beras", 30000}};

    // 3. Tree: Kategori Barang
    KategoriNode *root = new KategoriNode("Makanan");
    root->kiri = new KategoriNode("Minuman");
    root->kanan = new KategoriNode("Pokok");

    cout << "===== Aplikasi Kasir =====" << endl;
    cout << "Nama pelanggan: ";
    getline(cin, namaPelanggan);
    antrean.push(namaPelanggan); // Queue (Antrean)

    do
    {
        cout << "\nMenu Kasir:\n";
        cout << "1. Tampilkan Daftar Barang\n";
        cout << "2. Tambah Barang ke Keranjang\n";
        cout << "3. Tampilkan Keranjang\n";
        cout << "4. Undo Tambah Terakhir\n";
        cout << "5. Lihat Total\n";
        cout << "6. Cek Kategori Barang\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            cout << "\nDaftar Barang:\n";
            for (int i = 0; i < 3; i++)
            {
                cout << daftarBarang[i].kode << " - " << daftarBarang[i].nama
                     << " - Rp" << daftarBarang[i].harga << endl;
            }
            break;
        case 2:
        {
            string kode;
            cout << "Masukkan kode barang: ";
            cin >> kode;
            for (int i = 0; i < 3; i++)
            {
                if (daftarBarang[i].kode == kode)
                {
                    belanja.tambahBarang(daftarBarang[i]);
                    undoStack.push(daftarBarang[i]); // Stack
                    cout << "Barang ditambahkan.\n";
                    break;
                }
            }
            break;
        }
        case 3:
            cout << "\nIsi Keranjang:\n";
            belanja.tampilkanBarang();
            break;
        case 4:
            if (!undoStack.empty())
            {
                belanja.hapusTerakhir();
                undoStack.pop(); // Stack
                cout << "Barang terakhir dihapus.\n";
            }
            else
            {
                cout << "Tidak ada yang bisa di-undo.\n";
            }
            break;
        case 5:
            cout << "Total belanja: Rp" << belanja.hitungTotal() << endl;
            break;
        case 6:
        {
            string cari;
            cout << "Masukkan kategori (Makanan/Minuman/Pokok): ";
            cin >> cari;
            if (cariKategori(root, cari))
                cout << "Kategori ditemukan!\n";
            else
                cout << "Kategori tidak ditemukan.\n";
            break;
        }
        case 0:
            cout << "Terima kasih telah berbelanja!\n";
            break;
        }
    } while (pilihan != 0);

    return 0;
}
