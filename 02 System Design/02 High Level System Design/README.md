# 1. Terms and Notes
1. Jargons
    - AZ : Availability Zones
    - Containerized microservices ??
2. Interview Flow :
    - Overview
    - Requirements (Functional and Non-Functional)
    - High level design
    - Low level design of focused items
    - Trade-offs / Drawbacks discussion
3. Non-Functional Requirements
    - Availability
        - e.g. 99.99% (52 min 32 sec downtime / year) 
    - Consistency
    - Fault Tolerant
    - Reliability
    - Scalability / Maintainability
4. Cloud Infrastructure Hierarchy
    - **Global Cloud Services Provider Network** (e.g., AWS / Azure / GCP)
      - Multiple **Regions** (by country/continent)
        - Multiple **Availability Zones (AZs)** (nearby <~100km)
          - Multiple **Data Centers**
            - Racks of **Physical Servers**:  (running virtual machines, containers (e.g., Docker/Kubernetes), storage nodes, etc.)
5. Components
 -  Client (Mobile / Web)
     - Send request  
 -  CDN (Content Delivery Network)
     - Spread geographically 
     - Serve cached media(images, audio, video) and static files(html/css)
     - Security (e.g. prevention from DDOS attack)
     - Goal : Load latency
     - e.g. Akamai
 -  Load Balancer
     - Balance/Distribute load/request between servers
     - Goal : Routing (High concurrency), Fault tolerance
     - Types :
         - ELB(Layer 4 in OSI) : IP/TCP/UDP-based (low latency, static IPs).
             - Handling non-HTTP traffic (e.g., TCP, UDP). Need ultra-low latency and static IPs e.g. gaming 
         - ALB(Layer 7) : HTTP-based (path/host/header routing).
             - Hosting modern HTTP apps or microservices. Route based on HTTP headers or paths
     - Algorithms for distruibution :
         - Consistent Hashing
         - Round Robin
         - Weighted Round robin
         - Least Connection 
 -  App Servers
 -  Message Queue
 -  Cache
6. Scaling
    - Vertical Scaling (increase RAM, CPU, memory of servers/machines) : Handle more load
    - Horizontal Scaling (large no. of servers working together) : : Handle more load
    - Replication : Availability
        - Master-Slave nodes (write to : master node, read from : slave nodes) 
    - Database Sharding (Partition)
7. Communication / Connection
    - APIs
    - Gatweway
8. System Architecture
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

9. Application Layer Architecture
    - Monolithic
    - Microservices
11. Mechanisms / Algorithms
    - Seat/Resource Blocking : e.g. Blocking Seat (Ticket Booking System)
        - timeout-based block mechanism
            - Redis based blocking technique with a defined TTL 
13. Product Deployment Strategy
    - Application layer : Isolated stacks, Common stack, Hybrid stack
14. Tools at our disposal
## 1. Messaging & Queuing Systems (for Asynchronous tasks)
- Apache Kafka  
- RabbitMQ  
- Amazon SQS  

## 2. Search Engines
- Elasticsearch  
- Apache Solr  

## 3. Databases
- MySQL  (ACID property)
- PostgreSQL  
- MongoDB  (Document-based NoSQL database)
- Cassandra  (Distributed NoSQL database for handling large amounts of data.)
- Redis  

## 4. Caching Systems
- Redis  
- Memcached  

## 5. API Gateways & Reverse Proxies
- Nginx  
- HAProxy  
- AWS API Gateway  

## 6. Load Balancers
- AWS Elastic Load Balancer (ELB)  
- Nginx  
- HAProxy  

## 7. Container Orchestration
- Kubernetes  
- Amazon ECS  
- Google Kubernetes Engine (GKE)  

## 8. Monitoring & Tracing
- Prometheus  
- Grafana  
- Datadog  
- Jaeger  

## 9. CI/CD & Automation
- Jenkins  
- GitLab CI/CD  
- CircleCI  

## 10. Storage & File Systems
- Amazon S3  
- Google Cloud Storage  
- HDFS (Hadoop Distributed File System)  

## 11. Data Processing & Analytics
- Apache Hadoop  
- Apache Spark  
- Google BigQuery  
- Amazon Redshift  

## 12. Authentication & Authorization
- OAuth2  
- JWT  
- Auth0  
- AWS Cognito  

## 13. Event-Driven Architecture
- Apache Kafka  
- AWS EventBridge  
- Google Pub/Sub  

## 14. Coordination & Service Management
- Apache ZooKeeper   

## 15. CDN
- Akamai  

## 16. Payment
- Third party payment gateways


      
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
## System Design Tools - Cheatsheet
<img width="876" alt="image" src="https://github.com/user-attachments/assets/46a319b6-58c8-4ce9-a2da-019c13892ebf" />

---
