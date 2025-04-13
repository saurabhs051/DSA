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
# 2. 🧱 System Design Architecture Examples (Interview-Focused)

---

## 1. URL Shortener (e.g., bit.ly)
Key Concepts: Read-heavy, cache, hash generation, scalability.
- Frontend/API: API Gateway + Nginx  
- Hash Generation: App Layer with Base62 encoding  
- Database: Redis (cache), PostgreSQL/MySQL (storage)  
- Redirection Service: Stateless  
- Monitoring: Prometheus + Grafana  

---

## 2. Rate Limiter
Key Concepts: Throttling, fairness, distributed cache.
- Approach: Token bucket / Sliding window  
- Cache Layer: Redis or Memcached  
- Proxy Layer: Nginx with Lua scripts / API Gateway  
- Auth: JWT  

---

## 3. News Feed System (e.g., Facebook)
Key Concepts: Fan-out vs pull, ranking, real-time updates.
- User Actions → Kafka  
- Feed Generation Service: Kafka Consumers + Redis  
- Database: MongoDB or Cassandra  
- Recommendation: Spark or ML Service  
- Media Storage: Amazon S3  
- Search: Elasticsearch  

---

## 4. Chat Application (e.g., WhatsApp, Slack)
Key Concepts: Real-time messaging, pub/sub, delivery guarantees.
- WebSocket Servers: Nginx + App Layer  
- Message Broker: Kafka or RabbitMQ  
- User Sessions: Redis  
- Chat History: Cassandra or MongoDB  
- Push Notifications: Firebase / SNS  
- Auth: OAuth2 + JWT  

---

## 5. YouTube-like Video Platform
Key Concepts: Video storage, encoding pipeline, CDN.
- Upload Service → S3  
- Encoding: EventBridge + Lambda + FFmpeg containers
- Metadata DB: PostgreSQL  
- Search: Elasticsearch  
- Video Serving: CDN (CloudFront / Akamai)  
- Recommendations: Spark + ML  
- Comments & Likes: MongoDB or Cassandra  

---

## 6. Instagram / Pinterest Clone
Key Concepts: Media storage, user timelines, notifications.
- Upload: S3  
- Metadata DB: PostgreSQL  
- Image Processing: Lambda / Spark  
- Timeline: Redis  
- Search: Elasticsearch  
- Notifications: Kafka  
- CDN: CloudFront  

---

## 7. E-Commerce Platform (e.g., Amazon)
Key Concepts: Catalog, order management, cart, payment flow.
- Product Catalog: PostgreSQL + Redis  
- Cart: Redis  
- Order Service: RabbitMQ + MongoDB  
- Payments: External Gateway + Kafka  
- Inventory Management: Cassandra  
- Search: Elasticsearch  
- File Storage: S3  
- Auth: OAuth2 + Cognito  
- Monitoring: Prometheus, Grafana, Jaeger  

---

## 8. Twitter Clone
Key Concepts: High write volume, fan-out strategy, scalability.
- Tweet Ingest: Kafka  
- User Timeline: Redis (Fan-out-on-write)  
- Tweet DB: Cassandra  
- User Graph: Neo4j / PostgreSQL  
- Search: Elasticsearch  
- Media Upload: S3  

---

## 9. Dropbox / Google Drive
Key Concepts: File chunking, sync, versioning, metadata storage.
- File Storage: S3 / GCS  
- Metadata DB: PostgreSQL  
- File Chunking: App Layer + Redis  
- Sharing / ACL: OAuth  
- Sync Engine: Kafka + Consumers  
- Versioning: Append-only writes  

---

## 10. Online Code Editor / IDE
Key Concepts: Real-time collab, isolated execution, autosave.
- Collab Sync: WebSocket + Redis pub/sub  
- Execution Engine: Docker + K8s  
- File Storage: S3  
- User Data: PostgreSQL  
- CI Integration: Jenkins / GitLab CI  

---

## 11. Design Google Docs
Key Concepts: Operational transformation / CRDTs, real-time sync.
- Editor: WebSocket / WebRTC + Redis Channels  
- Document Storage: MongoDB / PostgreSQL  
- Versioning: Append-only log  
- Real-Time OT Engine  
- Search: Elasticsearch  
- Backup: S3  

---

## 12. Design Uber / Lyft
Key Concepts: Real-time location tracking, matching engine.
- Location Updates: Kafka → Redis (geo-indexed)  
- Matching Service: App Layer + Redis  
- Database: PostgreSQL (rides), Cassandra (logs)  
- Pricing Engine: Spark / Lambda  
- Notifications: SNS  
- Maps / Routing: Google Maps API / OpenStreetMap  

---

## 13. Design a Scalable Notification System
Key Concepts: Multi-channel (email, SMS, push), batching, retries.
- Event Producer: Kafka  
- Notification Workers: RabbitMQ  
- Channel Dispatcher: SNS, SES, FCM  
- Template Store: Redis or S3  
- Failure Queue: Dead-letter Queue (DLQ)  

---

## 14. Multiplayer Game Server (Real-Time)
Key Concepts: Low-latency sync, state replication.
- Game Engine: WebSocket Server (Node.js/Go)  
- State Sync: Redis pub/sub  
- Matchmaking: Redis / MongoDB  
- Metrics: Prometheus + Grafana  

---

## 15. Real-Time Analytics Platform
Use Case: User actions tracked in real-time, processed for metrics and dashboards.
- Producer: Kafka  
- Consumer: Spark  
- Processed Data: Cassandra / Redshift  
- Searchable Logs: Elasticsearch  
- Dashboards: Grafana  
- Coordination: ZooKeeper  
- API Layer: Nginx + JWT Auth  

---

## 16. E-commerce Web App
Use Case: High availability, search, order management.
- Frontend: API Gateway (AWS)  
- Backend Services: Kubernetes  
- Product Catalog: PostgreSQL / Redis cache  
- Search: Elasticsearch  
- Order Queue: RabbitMQ  
- Payments: EventBridge  
- File Storage: Amazon S3  
- Auth: AWS Cognito + OAuth2  
- Monitoring: Prometheus + Grafana  

---

## 17. Microservices-Based Social Media App
Use Case: Post, comment, like, notifications at scale.
- API Gateway → Microservices on Kubernetes  
- Post/Comment DB: MongoDB  
- Feed Generation: Kafka Streams  
- Notification Service: Kafka + Redis Queue  
- Media Uploads: S3  
- Search: Elasticsearch  
- Auth: Auth0 + JWT  
- Observability: Jaeger, Prometheus, Grafana  

---

## 18. YouTube-like Video Platform (Extended)
Use Case: Video upload, search, streaming, recommendations.
- Frontend: API Gateway (Nginx)  
- Backend: Microservices (K8s)  
- Metadata: MySQL  
- Search: Elasticsearch  
- Video Storage: S3  
- Video Encoding: EventBridge + Lambda Workers  
- Recommendations: Spark + Cassandra  
- CDN: CloudFront or similar  

      
---
# 3. Images
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
