# DigitalOcean Snapshot Automation (Makefile)

This project provides a simple **Makefile-based automation** for managing DigitalOcean droplets and snapshots باستخدام `curl` و `jq`.

It replicates the behavior of the original PHP script:

* 📦 Creates snapshots for droplets with a specific tag
* 🧹 Deletes old snapshots based on rules

---

## ⚙️ Requirements

Make sure the following tools are installed:

* `curl`
* `jq`
* GNU `date` (Linux environment recommended)

Install `jq` on Ubuntu/Debian:

```bash
sudo apt install jq
```

---

## 🔧 Configuration

Edit the `Makefile` and update:

```makefile
TOKEN := TOKEN HERE
TAG   := TAG NAME HERE
```

* `TOKEN`: Your DigitalOcean API token
* `TAG`: Tag used to filter droplets

---

## 🚀 Usage

### Run everything:

```bash
make
```

### Run individual tasks:

List droplets:

```bash
make droplets
```

List snapshots:

```bash
make snapshots-list
```

Delete old snapshots:

```bash
make cleanup
```

Create new snapshots:

```bash
make snapshots
```

---

## 🧠 Logic

### Snapshot Cleanup Rules

* Deletes snapshots if:

  * They are **not created on Friday**, OR
  * They are **created on Friday but older than 7 days**

### Snapshot Creation

* Finds all droplets with the specified tag
* Creates a snapshot for each droplet

---

## ⏱️ Automation (Cron Job)

To run daily at 2 AM:

```bash
crontab -e
```

Add:

```bash
0 2 * * * make -C /path/to/project
```

---

## ⚠️ Notes

* Requires a Linux environment (GNU `date`)
* macOS users may need to install `coreutils` and use `gdate`
* Ensure your API token has permission to:

  * Read droplets
  * Read snapshots
  * Create snapshots
  * Delete snapshots

---

## 📄 License

No license — use it freely.
