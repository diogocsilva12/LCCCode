import java.util.*;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;

class Bank {

    private static class Account {
        private int balance;
        Account(int balance) { this.balance = balance; }
        int balance() { return balance; }
        boolean deposit(int value) {
            balance += value;
            return true;
        }
        boolean withdraw(int value) {
            if (value > balance)
                return false;
            balance -= value;
            return true;
        }
    }

    private Map<Integer, Account> map = new HashMap<Integer, Account>();
    private int nextId = 0;
    private Lock l = new ReentrantLock();

    // create account and return account id
    public int createAccount(int balance) {
        Account c = new Account(balance);
        l.lock();
        try {
            int id = nextId;
            nextId += 1;
            map.put(id, c);
            return id;
        } finally {
            l.unlock();
        }
    }

    // close account and return balance, or 0 if no such account
    public int closeAccount(int id) {
        Account c;
        l.lock();
        try {
            Account c = map.remove(id);
            if (c == null)
                return 0;
            c.l.lock();
        } finally {
            l.unlock();
        }
        try {
            return c.balance();
        } finally {
            c.l.unlock();
        }
        
    }

    // account balance; 0 if no such account
    public int balance(int id) {
        Account c = map.get(id);
        if (c == null)
            return 0;
        return c.balance();
    }

    // deposit; fails if no such account
    public boolean deposit(int id, int value) {
        Account c = map.get(id);
        if (c == null)
            return false;
        return c.deposit(value);
    }

    // withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        Account c = map.get(id);
        if (c == null)
            return false;
        return c.withdraw(value);
    }

    // transfer value between accounts;
    // fails if either account does not exist or insufficient balance
    public boolean transfer(int from, int to, int value) {
        Account cfrom = map.get(from);
        Account cto = map.get(to);
        l.lock();
        try {
            
            if (cfrom == null || cto == null)
                return false;
            return cfrom.withdraw(value) && cto.deposit(value);
        } finally {
            l.unlock();
        }
    }

    // sum of balances in set of accounts; 0 if some does not exist
    public int totalBalance(int[] ids) {
        int total = 0;
        for (int i : ids) {
            Account c = map.get(i);
            if (c == null)
                return 0;
            total += c.balance();
        }
        return total;
    }

}
