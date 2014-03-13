function Core()
{
    Core.prototype.initialize = function()
    {
		rhChat.playSound.connect(playSound);
        rhChat.markLoaded.connect(markLoaded);
        rhChat.addTextMessage.connect(addTextMessage);
        rhChat.addInfoMessage.connect(addInfoMessage);
        rhChat.addTypingMessage.connect(addTypingMessage);
        rhChat.redirected.connect(redirected);
        rhChat.startRedirect.connect(startRedirect);
        rhChat.confirmRedirect.connect(confirmRedirect);
        rhChat.failRedirect.connect(failRedirect);
        rhChat.seize.connect(seize);
    }
	
	function playSound()
	{
        $('#audio')[0].play();
	}

    function markLoaded()
    {
        $('#loading').hide();
    }

    function addTextMessage(source, sender, message_id, time, text)
    {
        core.addMessage(source, sender, message_id, time, text);
    }

    function addInfoMessage(time, text)
    {
        console.log("adding information " + text);
    }

    function addTypingMessage(text)
    {
        $('#typing .text').html(text);
        $('#typing').show();
        $(window).scrollTop($(document).height());
    }

    function redirected(message)
    {
        core.startRedirect(message);
    }

    function startRedirect(message)
    {
        core.startRedirect(message);
    }

    function confirmRedirect(message)
    {
        core.startRedirect(message);
    }

    function failRedirect(message)
    {
        core.startRedirect(message);
    }

    function seize(message)
    {
        core.startRedirect(message);
    }


    Core.prototype.useTemplate = function(template_name, vars)
    {
        template = $('.templates #' + template_name).html();
        for(var field in vars)
        {
            var re = new RegExp('{{' + field + '}}', 'g');
            template = template.replace(re, vars[field]);
        }
        return template;
    }

    Core.prototype.getBlock = function(source, sender, time)
    {
        var block = $('#chat .msgBlock:last');
        if (block.length>0 && block.hasClass('from'+source))
            return block;
        template = this.useTemplate('message_block_template', {source:source, sender: sender});
        $('#chat').append(template);
        return $('#chat .msgBlock:last');
    }

    Core.prototype.addMessage = function(source, sender, message_id, time, text)
    {
        $('#typing').hide();
        block = this.getBlock(source, sender, time)
        template = this.useTemplate('message_template', {message_id:message_id, time:time, message:text});
        block.append(template);

        $(window).scrollTop($(document).height());
    }

    Core.prototype.startRedirect = function(message)
    {
        template = this.useTemplate('redirect_template', {message_id:'', time:'', message:message});
        $('#chat').append(template);

        $(window).scrollTop($(document).height());
    }

    Core.prototype.test = function(){
        for(var i=0;i<1000;i++)
        {
            var source = 'Visitor';
            var sender = '#1135031'
            var message = 'Привет! Я хочу купить у вас автомобиль <a href="http://redhelper.ru#123" target="_blank">БТР</a>. Можно заказать драйв-тест? И в какие расцветки доступны?';
             if (Math.random()<0.5)
             {
                 source = 'Operator';
                 sender = 'Вася Пупкин';
                 message = 'К сожалению, все БТР уже закончились. Можем предложить вам отличный седан Т-34! Отличная проходимость! Не требовательный к топливу. Может парковаться не зависимо от занятости парковочного места';
             }
            core.addMessage(source, sender, '32312312312312', '12:09', message);
        }
    }
    //$(Core.prototype.test);
}

window.core = new Core();
$(window.core.initialize);
