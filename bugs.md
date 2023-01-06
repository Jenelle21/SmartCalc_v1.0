<h2>Bugs found so far.</h2>

1. **Problem with deposits created on the 29th-31st of the month:**\
Rollback to the last day of the month added to match calculations on calcus.ru.
So after a short month(February) the payment date is shifted.
2. **Problem with several partial withdrawals/replenishments in one day:**
Broken function of filtering out duplicate dates