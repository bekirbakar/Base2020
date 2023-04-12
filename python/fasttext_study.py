import fasttext

try:
    model = fasttext.load_model('./cc.tr.300.bin')
except:
    raise Exception('Model not found!')

model.get_dimension()
model.get_dimension()

print(model.get_word_vector('selam'))
