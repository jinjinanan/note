# HiNovel

- 小说阅读器
- 漫画阅读器
- iap

## IAP

取得商品的 product ID -> 创建订单 -> 使用 product ID 从apple服务器获取商品信息 -> 开始购买 -> 產生代表交易的 SKPayment 進行購買。-> 從 SKPaymentTransactionObserver 的 function 判斷交易的結果。 -> 若交易成功則提供商品給使用者。

### 丢单原因

1. 第一步，客户端发起支付之后，苹果那边正在处理支付，客户端由于某种原因被kill了，支付结果并不能返回到客户端，但是苹果那边确实扣款成功。
2. 第二步，客户端拿到支付结果和支付凭证之后，向服务端发送App Receipt票据之前，客户端被kill，也会导致扣款成功，服务端订单状态没有修改。

### 解决办法

原因一

1. 在生成订单的时候存储我们自己的订单信息 
2. 可以在 App 一启动就设置监听，如果有未完成的支付，则会回调- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions; （解决问题一）
3. 如果收到回掉但是却没有取到交易凭证，这样的订单finish掉并返回
4. 如果有交易凭证，将订单号，App Receipt票据缓存到本地持久化到keychain当中 （解决丢单问题二）
5. 发起验证订单请求，服务端返回正确结果之后，将该缓存结果删除，结束本次交易。每次app启动之后，就检查是否有未删除的订单，如果有，就向服务端重试验证支付结果，服务端返回正确结果之后，将该缓存结果删除，结束本次交易。
6. 业务订单和iap订单通过productId 绑定 [订单绑定](https://juejin.cn/post/6844903538259132430)
