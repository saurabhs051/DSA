# 1. SOLID Principles

### Summary
(Talks about inheritance and has a relationship: Basically avoid tight coupling)

1. **S** : Class chote banao
2. **O** : Interface banao, Inheritance use karo
3. **L** : Inheritance sahi se karo, relatable hona chahiye
4. **I** : Interface chote banao
5. **D** : Data member should be Interface, concrete class nhi

---

### 🔍 Details

| Principle                          | Concept                                                                 | Focus                                                       | Example                                                                                                                                                                                                 |
|------------------------------------|-------------------------------------------------------------------------|-------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Single Responsibility Principle (SRP)** | A class should have only one reason to change.                            | Focus on small, modular classes, not "FAT" modules.          | - **Incorrect (Vehicle Class):**<br>  - `startEngine()`<br>  - `stopEngine()`<br>  - `printVehicleDetails()` (should be in a VehiclePrinter class)<br><br> - **Incorrect (Bakery Class):**<br>  - `bake()`<br>  - `manageInventory()` (should be in a Manager class)<br>  - `serveCustomers()` (should be in a Waiter class) |
| **Open/Closed Principle (OCP)**    | Open for extension, closed for modification.                             | Avoid adding if-else statements for new functionality. Use inheritance or interfaces instead. | - **Incorrect (Staff Class):**<br>  - `if Baker: salary()`<br>  - `else if Manager: salary()`<br>  - `else if Waiter: salary()`<br><br> - **Correct Approach:**<br>  - `Staff` (base class)<br>  - `Baker` (inherits from Staff, implements `salary()`)<br>  - `Manager` (inherits from Staff, implements `salary()`)<br>  - `Waiter` (inherits from Staff, implements `salary()`) |
| **Liskov Substitution Principle (LSP)** | Base class instances should be replaceable by derived class instances without altering the correctness of the program. | Inherit properly. Derived classes should not require extra behaviors. | - **Incorrect:**<br>  - `Rectangle` class<br>  - `Square` inherits from `Rectangle` (Square tries to fit into Rectangle’s behavior, which is wrong)<br><br> - **Incorrect:**<br>  - `Vehicle`<br>  - `Bicycle` (won’t use a `drive()` method)<br>  - Might add extra methods |
| **Interface Segregation Principle (ISP)** | Clients should not be forced to implement methods they don't use.         | Keep interfaces small, not "FAT". Multiple inheritance karna is better | - **Incorrect:**<br>  - `Vehicle` interface with `drive()` and `fly()`<br>  - `Aeroplane` (uses `drive()`, would have to add empty `fly()` implementation)<br>  - `Car` (won’t use `fly()`)<br><br> - **Correct Approach:**<br>  - Separate interfaces: `Drivable`, `Flyable`<br>  - `Car` → Drivable<br>  - `Aeroplane` → Flyable<br>  - `NewEraVehicle` → Drivable, Flyable |
| **Dependency Inversion Principle (DIP)** | High-level modules should not depend on low-level modules. Both should depend on abstractions (interfaces). | "Has a" relationship / data members should be Interfaces, not concrete classes. | - **Incorrect:** Car class directly depends on `DieselEngine` class.<br> - **Correct Approach:** Depend on an `Engine` interface, which `DieselEngine` implements. Allows for `ElectricEngine` in future. |


