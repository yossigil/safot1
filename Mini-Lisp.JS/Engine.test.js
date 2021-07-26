const p = require('./Parser')
const Engine = require('./Engine')

const t = p.parse('t')
const nil = p.parse('nil')
const a = p.parse('a')
const b = p.parse('b')

test('evaluate', () => {	
	const e = new Engine()
	expect(e.evaluate(p.parse("(car '(a . b))"))).toStrictEqual(a)
	expect(e.evaluate(p.parse("(car '(b a x y z))"))).toStrictEqual(b)
	expect(e.evaluate(p.parse("(cdr '(a . b))"))).toStrictEqual(b)
	expect(e.evaluate(p.parse("(cdr '(b a x y z))"))).toStrictEqual(p.parse('(a x y z)'))
	expect(e.evaluate(p.parse("(quote a)"))).toStrictEqual(a)
	expect(e.evaluate(p.parse("(atom 'a)"))).toStrictEqual(t)
	expect(e.evaluate(p.parse("(atom '(a . b))"))).toStrictEqual(nil)
	expect(e.evaluate(p.parse("(null nil)"))).toStrictEqual(t)
	expect(e.evaluate(p.parse("(null 'a)"))).toStrictEqual(nil)
	expect(e.evaluate(p.parse("(eq 'a 'a)"))).toStrictEqual(t)
	expect(e.evaluate(p.parse("(eq 'a 'b)"))).toStrictEqual(nil)
	expect(e.evaluate(p.parse("(eq 'a '(a . b))"))).toStrictEqual(nil)
	expect(e.evaluate(p.parse("(set 'a '(a . a))"))).toStrictEqual(p.parse("(a . a)"))
})