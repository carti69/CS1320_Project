# 📝 Git Workflow Cheat Sheet (Terminal Edition)

## ✅ Setup

```bash
git clone https://github.com/carti69/CS1320_Project
cd CS1320_Project
```

## 🆕 Starting a Feature / Fix

```bash
git checkout -b feature/branch-name
```
> Creates and switches to a new branch (e.g., `feature/score-tracking`)

## 💾 Add + Commit Your Changes

```bash
git add main.c
git commit -m "Short message describing the change"
```

## ☁️ Push Your Branch to GitHub

```bash
git push -u origin feature/branch-name
```
> The `-u` sets upstream so next time you can just run `git push`

## 🔁 Open a Pull Request (On GitHub)

- Go to your repo on GitHub
- Click "Compare & pull request"
- Describe your changes and click **Create pull request**
- Wait for approval or self-merge if solo

## ⬇️ After Merge: Sync `main`

```bash
git checkout main
git pull origin main
```

## 🧹 Delete Merged Branches

### 🔸 Locally:

```bash
git branch -d feature/branch-name
```

> Use `-D` (uppercase) if the branch hasn’t been merged and you want to force-delete.

### 🔸 On GitHub:

```bash
git push origin --delete feature/branch-name
```

## 🧠 Helpful Status & Logs

```bash
git status            # Shows changes, staged files, branch
git log --oneline     # Compact commit history
git branch            # List all local branches
git remote -v         # Check GitHub link (origin)
```

## 🚨 Pro Tips for Teams

- Set branch protection on `main` to **require pull requests**
- Use descriptive branch names:
  - `feature/xyz`
  - `bugfix/xyz`
  - `refactor/xyz`
- Keep pull requests small and focused
- Always sync `main` before starting new work:
  ```bash
  git checkout main
  git pull origin main
  git checkout -b feature/new-task
  ```
