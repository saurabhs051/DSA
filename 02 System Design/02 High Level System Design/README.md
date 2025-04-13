# 1. Terms and Notes
1. Interview Flow :
    - Overview
    - Requirements (Functional and Non-Functional)
    - High level design
    - Low level design of focused items
    - Trade-offs / Drawbacks discussion
2. Non-Functional Requirements
    - Availability
        - e.g. 99.99% (52 min 32 sec downtime / year) 
    - Consistency
    - Fault Tolerant
    - Reliability
    - Scalability / Maintainability
3. Communication / Connection
    - APIs
    - Gatweway
4. System Architecture
    - 3-Tier Architecture
        - Presentation Layer (UI)
            - developed using any modern JS frameworks like ReactJS, NextJS, VueJS and many more 
        - Application Layer (Application servers)
            - microservices-oriented architecture
            - Each microservice can implement a "Hexagonal design pattern" 
        - Persistence / Storage Layer (Database, Cache, OLAP, OLTP)
            - OLTP :
                - Online Transaction Processing (Transaction processing - optimized for writes, concurrency, ACID property)
            - OLAP :
                - Online Analytical Processing  (Analytical processing - optimized for Business Intelligence - reads, analyze large volume of historical data)
                - Supports trend analysis, forecasting, and data mining. Typically involves data warehouses.
                - Examples: Sales forecasting reports, Financial analysis dashboards, Customer behavior analytics

6. Application Layer Architecture
    - Monolithic
    - Microservices
11. Mechanisms / Algorithms
    - Seat/Resource Blocking : e.g. Blocking Seat (Ticket Booking System)
        - timeout-based block mechanism
            - Redis based blocking technique with a defined TTL 
13. Product Deployment Strategy
    - Application layer : Isolated stacks, Common stack, Hybrid stack
      
---
# 2. Images
## OLAP vs OLTP
<img width="826" alt="image" src="https://github.com/user-attachments/assets/a205abca-b6d7-4050-ae27-f1f4790f5b87" />

---
## 3-Tier Architecture
<img width="521" alt="image" src="https://github.com/user-attachments/assets/0053de1e-f4be-4b23-8b35-027aca617395" />

----
## Product Deployment strategy - Hybrid stack 
<img width="762" alt="image" src="https://github.com/user-attachments/assets/e430f86a-4d0b-4b7c-9559-53cc9fff12b1" />

---

