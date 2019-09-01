const processText = (txt, limit=1) => txt.replace(/\n/g, '')
        .split(' ')
        .filter(i => i.length > limit)
        .join(' '); 

modules.export = {
  processText
}

