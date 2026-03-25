from google import genai

client = genai.Client(api_key="AIzaSyDmssGGvD2Ur5AFfgZAR8ZHSOUtE_8YUgU")

models = client.models.list()

for model in models:
    print(model.name, model.supported_actions)
