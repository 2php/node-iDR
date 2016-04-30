var iDR = require('./lib/RoutonRead');

var cardInfo = iDR.readCard();
if(cardInfo)
{
	console.log('姓名:', cardInfo.name);
	console.log('性别:', cardInfo.gender);
	console.log('民族:', cardInfo.folk);
	console.log('生日:', cardInfo.birthDay);
	console.log('身份证号码:', cardInfo.code);
	console.log('地址:', cardInfo.address);
	console.log('签证机关:', cardInfo.agency);
	console.log('有效期起始日期:', cardInfo.expireStart);
	console.log('有效期截至日期:', cardInfo.expireEnd);
}
else{
	console.log('读取身份证信息失败！');
}

process.on('uncaughtException', function (err) {
    console.log(err);
});

process.stdin.resume();
